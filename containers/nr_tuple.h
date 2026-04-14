#pragma once

namespace nr {
    
template<typename... Args>
class CTuple;
    
template<>
class CTuple<>;

template<typename Head, typename... Tail>
class CTuple<Head, Tail...> : private CTuple<Tail...> {
public:

private:
    Head value_;
};

} // namespace nr