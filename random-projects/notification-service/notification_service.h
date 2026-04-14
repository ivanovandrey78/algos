#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <cstdio>
#include <utility>
#include <vector>
#include <sstream>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const char* message) = 0;
};
 
class ConsoleLogger : public ILogger {
public:
    void log(const char* message) override {
        std::cout << message << std::endl;
    }
};

class FileLogger : public ILogger {
public:
    enum class LOG_LEVEL { DEBUG, INFO, WARN, ERROR };

    FileLogger(const char* path) {
        file_ = fopen(path, "w");
    }

    ~FileLogger() {
        if (file_) { fclose(file_); }
    }

    void log(const char* message) override {
        fputs(message, file_);
    }

    template<typename... Args>
    void log(FileLogger::LOG_LEVEL type, Args... args) {
        switch (type) {
            case LOG_LEVEL::DEBUG: fputs("[DEBUG] ", file_); break;
            case LOG_LEVEL::INFO : fputs("[INFO] ", file_);  break;
            case LOG_LEVEL::WARN : fputs("[WARN] ", file_);  break;
            case LOG_LEVEL::ERROR: fputs("[ERROR] ", file_); break;
        }
        std::stringstream oss;
        ((oss << args << ' '), ...); oss << std::endl;
        fputs(oss.str().c_str(), file_);
    }

private:
    FILE* file_;
};

class IDataBase {
public: 
    using Info = std::pair<std::string, std::string>;

    virtual ~IDataBase() = default;
    virtual void AddUser(std::string user, 
                         std::string email, 
                         std::string phone) = 0;

    virtual std::string GetEmail(const std::string& userId) const = 0;
    virtual std::string GetPhoneNumber(const std::string& userId) const = 0;
    virtual void SaveToHistory(const std::string& user) = 0;
    virtual void PrintHistory() const = 0;

protected:
    virtual Info GetInfo(const std::string& userId) const = 0;
};

class MySQL : public IDataBase {
public:
    MySQL() = default;
    ~MySQL() = default;

    void AddUser(std::string user,
                 std::string email, 
                 std::string phone) override 
    {
        Info tmp(email, phone);
        data_[user] = tmp;
    }

    std::string GetEmail(const std::string& userId) const override {
        return GetInfo(userId).first;
    }

    std::string GetPhoneNumber(const std::string& userId) const override {
        return GetInfo(userId).second;
    }

    void SaveToHistory(const std::string& user) override {
        std::cout << "Saving to MySQL: notification sent to " << user << "\n";
        history_.push_back(user);
    }

    void PrintHistory() const override {
        for (const auto u : history_) {
            std::cout << "Saving to Data Base: notification sent to " 
                      << u << "\n";
        }
    }

private:
    Info GetInfo(const std::string& userId) const override {
        auto it = data_.find(userId);
        if (it != data_.end()) { return it->second; }
        throw std::runtime_error("User isn't find!");
    }

    std::unordered_map<std::string, Info> data_;
    std::vector<std::string> history_;
};

class INotificationService {
public:
    virtual ~INotificationService() = default;

    virtual void SendNotification(const std::string& userId, 
                          const std::string& message) = 0;
};

class EmailNotificationService : public INotificationService {
public: 
    EmailNotificationService(ILogger& logger, IDataBase& db) 
        : logger_(logger),
          db_(db)
          {}

    void SendNotification(const std::string& userId, 
                          const std::string& message) override {
        std::string log_string =  "Sending email to " + userId + "\n";
        logger_.log(log_string.c_str());

        std::cout << "Sending EMAIL to " 
                  << db_.GetEmail(userId) 
                  << ": " << message << "\n";

        db_.SaveToHistory(userId);
    }

    static std::unique_ptr<INotificationService> Create(ILogger& logger, IDataBase& db) {
        return std::make_unique<EmailNotificationService>(logger, db);
    }

private:
    ILogger& logger_;
    IDataBase& db_;
};

class PhoneNotificationService : public INotificationService {
public: 
    PhoneNotificationService(ILogger& logger, IDataBase& db) 
        : logger_(logger),
          db_(db)
          {}

    void SendNotification(const std::string& userId, 
                          const std::string& message) override {
        std::string log_string =  "Sending sms to " + userId + "\n";
        logger_.log(log_string.c_str());

        std::cout << "Sending SMS to " 
                  << db_.GetPhoneNumber(userId) 
                  << ": " << message << "\n";

        db_.SaveToHistory(userId);
    }

    static std::unique_ptr<INotificationService> Create(ILogger& logger, IDataBase& db) {
        return std::make_unique<PhoneNotificationService>(logger, db);
    }

private:
    ILogger& logger_;
    IDataBase& db_;
};

class PushNotificationService : public INotificationService {
public: 
    PushNotificationService(ILogger& logger, IDataBase& db) 
        : logger_(logger),
          db_(db)
          {}

    void SendNotification(const std::string& userId, 
                          const std::string& message) override {
        std::string log_string =  "Sending push to " + userId + "\n";
        logger_.log(log_string.c_str());

        std::cout << "Sending PUSH to " 
                  << userId << ": " 
                  << message << "\n";

        db_.SaveToHistory(userId);
    }

    static std::unique_ptr<INotificationService> Create(ILogger& logger, IDataBase& db) {
        return std::make_unique<PushNotificationService>(logger, db);
    }

private:
    ILogger& logger_;
    IDataBase& db_;
};

class NotificationServiceFabric {
public:
    using CreatorFunc = std::unique_ptr<INotificationService>(*)(ILogger& logger, IDataBase& db);

    NotificationServiceFabric() = default;
    ~NotificationServiceFabric() = default;

    void Register(const std::string& name, CreatorFunc creator) {
        registry_[name] = creator;
    }

    std::unique_ptr<INotificationService> Create(const std::string& name,
                                                 ILogger& logger, 
                                                 IDataBase& db) {
        auto it = registry_.find(name);
        if (it != registry_.end()) { return it->second(logger, db); }
        throw std::runtime_error("Name wasn't find");
    }

    void PrintRegistry() const {
        for (const auto& pair : registry_) {
            std::cout << "- " << pair.first << std::endl;
        }
    }

private:
    std::unordered_map<std::string, CreatorFunc> registry_;
};

inline void Test() {
    // Logger
    FileLogger file_logger("notifications.log");
    ConsoleLogger console_logger;

    // Data base
    MySQL my_sql_db;
    my_sql_db.AddUser("user111", "golang@mail.en", "+5-901-102");
    my_sql_db.AddUser("user849", "cxx@mail.en", "+6-123-523");
    my_sql_db.AddUser("user410", "rustlang@mail.en", "+9-732-192");

    // Service Fabric
    NotificationServiceFabric nt_fabric;
    nt_fabric.Register("sms", PhoneNotificationService::Create);
    nt_fabric.Register("email", EmailNotificationService::Create);
    nt_fabric.Register("push", PushNotificationService::Create);

    // Creating
    auto email_service = nt_fabric.Create("email", file_logger, my_sql_db);
    auto push_service = nt_fabric.Create("push", file_logger, my_sql_db);
    auto sms_service = nt_fabric.Create("sms", file_logger, my_sql_db);

    // Testing
    // Fabric
    nt_fabric.PrintRegistry();
    std::cout << std::endl;

    // Sending
    email_service->SendNotification("user111", "Hello, man!");
    sms_service->SendNotification("user849", "So spicy!");
    push_service->SendNotification("user410", "Little Nighmares!");
    std::cout << std::endl;

    // History
    my_sql_db.PrintHistory();
}