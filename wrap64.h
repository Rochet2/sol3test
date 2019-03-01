#ifndef WRAP_64_H
#define WRAP_64_H

#include <cstdint> // (u)int64_t, (u)int32_t, (U)INT64_C
#include <cstddef> // size_t
#include <functional> // std::hash
#include <iomanip> // std::hex
#include <sstream> // std::stringstream
#include <string> // std::sto(u)ll
#include <type_traits> // std::enable_if, std::is_signed

template<typename T>
class wrap64
{
public:
    wrap64() noexcept : raw(0) { }
    wrap64(T raw) : raw(raw) { }
    wrap64(uint32_t hi, uint32_t lo) : raw((T(hi) << 32) | T(lo)) { }
    template<typename R = std::string const &>
    explicit wrap64(std::enable_if_t<std::is_signed<T>::value, R> s) : raw(strtoll(s)) { }
    template<typename R = std::string const &>
    explicit wrap64(std::enable_if_t<std::is_unsigned<T>::value, R> s) : raw(strtoull(s)) { }

    operator T() const { return raw; }
    uint32_t high() const { return raw >> 32; }
    uint32_t low() const { return raw & 0xFFFFFFFF; }
    bool empty() const { return raw == 0; }
    bool operator==(wrap64<T> const& w64) const { return raw == w64.raw; }
    bool operator!=(wrap64<T> const& w64) const { return raw != w64.raw; }
    bool operator<(wrap64<T> const& w64) const { return raw < w64.raw; }
    bool operator>(wrap64<T> const& w64) const { return raw > w64.raw; }
    bool operator<=(wrap64<T> const& w64) const { return raw < w64.raw || raw == w64.raw; }
    bool operator>=(wrap64<T> const& w64) const { return raw > w64.raw || raw == w64.raw; }
    // implement sum, division, multiplication, substraction, negation

    bool fitsdouble() const { return FitsDouble(raw); }
    double to_double() const { return static_cast<double>(raw); }
    std::string to_string() const { return std::to_string(raw); };
    std::string to_hex() const {
        return ToHex(raw);
    };
    T raw;

    static std::string ToHex(uint64_t raw) {
        std::ostringstream oss;
        oss << "0x" << std::hex << std::uppercase << raw;
        return oss.str();
    }
    static std::string ToHex(int64_t raw) {
        std::ostringstream oss;
        if (raw < 0)
            oss << "-0x" << std::hex << std::uppercase << (-raw);
        else
            oss << "0x" << std::hex << std::uppercase << raw;
        return oss.str();
    }
    static uint64_t strtoll(std::string const & s)
    {
        try { return std::stoll(s, 0, 0); }
        catch (std::invalid_argument) { return 0; }
        catch (std::out_of_range) { return 0; }
    }
    static uint64_t strtoull(std::string const & s)
    {
        try { return std::stoull(s, 0, 0); }
        catch (std::invalid_argument) { return 0; }
        catch (std::out_of_range) { return 0; }
    }
    static bool FitsDouble(uint64_t raw) { return raw <= UINT64_C(0x20000000000000); }
    static bool FitsDouble(int64_t raw) { return raw <= INT64_C(0x20000000000000) && raw >= INT64_C(-0x20000000000000); }
};

namespace std
{
    template<>
    struct hash<wrap64<uint64_t>>
    {
    public:
        size_t operator()(wrap64<uint64_t> const& key) const
        {
            return std::hash<uint64_t>()(key.raw);
        }
    };
    template<>
    struct hash<wrap64<int64_t>>
    {
    public:
        size_t operator()(wrap64<int64_t> const& key) const
        {
            return std::hash<int64_t>()(key.raw);
        }
    };
}

#endif
