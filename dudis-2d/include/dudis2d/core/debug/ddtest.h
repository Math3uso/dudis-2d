#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace dudis
{
    namespace debug
    {
        class Test
        {
        public:
            template <typename T>
            class Expectation
            {
            public:
                using Value = std::decay_t<T>;

                Expectation(T &&value, const char *label, const char *file, int line)
                    : actual_(std::forward<T>(value)), label_(label ? label : ""), file_(file), line_(line)
                {
                }

                template <typename U>
                Expectation &Equal(const U &expected)
                {
                    return Check("Equal", Equals(actual_, expected), expected, "");
                }

                template <typename U>
                Expectation &NotEqual(const U &expected)
                {
                    return Check("NotEqual", !Equals(actual_, expected), expected, "");
                }

                // template <typename U>
                // Expectation &Approx(const U &expected, const U &tolerance)
                // {
                //     static_assert(std::is_arithmetic_v<Value> && std::is_arithmetic_v<U>, "Approx requires arithmetic types");
                //     auto a = static_cast<long double>(actual_);
                //     auto e = static_cast<long double>(expected);
                //     auto t = static_cast<long double>(tolerance);
                //     bool ok = std::fabsl(a - e) <= t;
                //     return Check("Approx", ok, expected, std::string("tolerance=") + ToString(tolerance));
                // }

                Expectation &True()
                {
                    return Check("True", static_cast<bool>(actual_), "", "");
                }

                Expectation &False()
                {
                    return Check("False", !static_cast<bool>(actual_), "", "");
                }

                Expectation &Null()
                {
                    bool ok = false;
                    if constexpr (std::is_pointer_v<Value>)
                    {
                        ok = actual_ == nullptr;
                    }
                    return Check("Null", ok, "", "");
                }

                Expectation &NotNull()
                {
                    bool ok = false;
                    if constexpr (std::is_pointer_v<Value>)
                    {
                        ok = actual_ != nullptr;
                    }
                    return Check("NotNull", ok, "", "");
                }

                template <typename U>
                Expectation &Greater(const U &expected)
                {
                    return Check("Greater", actual_ > expected, expected, "");
                }

                template <typename U>
                Expectation &GreaterEqual(const U &expected)
                {
                    return Check("GreaterEqual", actual_ >= expected, expected, "");
                }

                template <typename U>
                Expectation &Less(const U &expected)
                {
                    return Check("Less", actual_ < expected, expected, "");
                }

                template <typename U>
                Expectation &LessEqual(const U &expected)
                {
                    return Check("LessEqual", actual_ <= expected, expected, "");
                }

                template <typename U>
                Expectation &Between(const U &low, const U &high)
                {
                    bool ok = actual_ >= low && actual_ <= high;
                    return Check("Between", ok, ToString(low) + ", " + ToString(high), "");
                }

                template <typename U>
                Expectation &Contains(const U &needle)
                {
                    bool ok = ContainsImpl(actual_, needle);
                    return Check("Contains", ok, needle, "");
                }

                template <typename Ex = std::exception>
                Expectation &Throws()
                {
                    bool ok = ThrowsImpl<Ex>();
                    return Check("Throws", ok, "", "");
                }

                Expectation &NotThrows()
                {
                    bool ok = NotThrowsImpl();
                    return Check("NotThrows", ok, "", "");
                }

            private:
                Value actual_;
                std::string label_;
                const char *file_;
                int line_;

                template <typename A, typename B>
                static bool Equals(const A &a, const B &b)
                {
                    if constexpr (std::is_same_v<std::decay_t<A>, const char *> || std::is_same_v<std::decay_t<A>, char *> ||
                                  std::is_same_v<std::decay_t<B>, const char *> || std::is_same_v<std::decay_t<B>, char *>)
                    {
                        return ToString(a) == ToString(b);
                    }
                    else
                    {
                        return a == b;
                    }
                }

                template <typename A>
                static std::string ToString(const A &value)
                {
                    if constexpr (std::is_same_v<std::decay_t<A>, std::string>)
                    {
                        return value;
                    }
                    else if constexpr (std::is_same_v<std::decay_t<A>, const char *> || std::is_same_v<std::decay_t<A>, char *>)
                    {
                        return value ? std::string(value) : std::string("<null>");
                    }
                    else if constexpr (std::is_same_v<std::decay_t<A>, bool>)
                    {
                        return value ? "true" : "false";
                    }
                    else if constexpr (std::is_arithmetic_v<std::decay_t<A>>)
                    {
                        std::ostringstream ss;
                        ss << std::setprecision(10) << value;
                        return ss.str();
                    }
                    else
                    {
                        if constexpr (IsStreamable<A>::value)
                        {
                            std::ostringstream ss;
                            ss << value;
                            return ss.str();
                        }
                        else
                        {
                            return std::string("<") + typeid(A).name() + ">";
                        }
                    }
                }

                template <typename A, typename = void>
                struct IsStreamable : std::false_type
                {
                };

                template <typename A>
                struct IsStreamable<A, std::void_t<decltype(std::declval<std::ostream &>() << std::declval<A>())>> : std::true_type
                {
                };

                static void LogResult(bool ok, const std::string &name, const std::string &actual, const std::string &expected, const std::string &extra, const std::string &label, const char *file, int line)
                {
                    if (!ok)
                    {
                        ++Test::Failed();
                    }
                    else
                    {
                        ++Test::Passed();
                    }
                    ++Test::Total();

                    if (!ok || Test::Verbose())
                    {
                        std::ostream &out = Test::Output();
                        out << (ok ? "[PASS] " : "[FAIL] ") << name;
                        if (!label.empty())
                        {
                            out << " | " << label;
                        }
                        if (!actual.empty())
                        {
                            out << " | actual=" << actual;
                        }
                        if (!expected.empty())
                        {
                            out << " | expected=" << expected;
                        }
                        if (!extra.empty())
                        {
                            out << " | " << extra;
                        }
                        if (file && line > 0)
                        {
                            out << " | " << file << ":" << line;
                        }
                        out << '\n';
                    }
                }

                template <typename E>
                Expectation &Check(const std::string &name, bool ok, const E &expected, const std::string &extra)
                {
                    LogResult(ok, name, ToString(actual_), ToString(expected), extra, label_, file_, line_);
                    return *this;
                }

                Expectation &Check(const std::string &name, bool ok, const char *expected, const std::string &extra)
                {
                    LogResult(ok, name, ToString(actual_), expected ? std::string(expected) : std::string(""), extra, label_, file_, line_);
                    return *this;
                }

                template <typename H, typename N>
                static bool ContainsImpl(const H &haystack, const N &needle)
                {
                    if constexpr (IsCStr<H>::value || IsCStr<N>::value)
                    {
                        std::string h = ToString(haystack);
                        std::string n = ToString(needle);
                        return h.find(n) != std::string::npos;
                    }
                    else if constexpr (std::is_same_v<std::decay_t<H>, std::string> && std::is_same_v<std::decay_t<N>, std::string>)
                    {
                        return haystack.find(needle) != std::string::npos;
                    }
                    else
                    {
                        using std::begin;
                        using std::end;
                        return std::find(begin(haystack), end(haystack), needle) != end(haystack);
                    }
                }

                template <typename A>
                struct IsCStr : std::bool_constant<std::is_same_v<std::decay_t<A>, const char *> || std::is_same_v<std::decay_t<A>, char *>>
                {
                };

                template <typename Ex>
                bool ThrowsImpl()
                {
                    if constexpr (std::is_invocable_v<Value>)
                    {
                        try
                        {
                            actual_();
                        }
                        catch (const Ex &)
                        {
                            return true;
                        }
                        catch (...)
                        {
                            return false;
                        }
                        return false;
                    }
                    else
                    {
                        return false;
                    }
                }

                bool NotThrowsImpl()
                {
                    if constexpr (std::is_invocable_v<Value>)
                    {
                        try
                        {
                            actual_();
                        }
                        catch (...)
                        {
                            return false;
                        }
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            };

            template <typename T>
            static Expectation<T> Expect(T &&value, const char *label = nullptr, const char *file = nullptr, int line = 0)
            {
                return Expectation<T>(std::forward<T>(value), label, file, line);
            }

            static void Reset()
            {
                Total() = 0;
                Passed() = 0;
                Failed() = 0;
            }

            static void SetVerbose(bool enabled)
            {
                Verbose() = enabled;
            }

            static void SetOutput(std::ostream &out)
            {
                OutputPtr() = &out;
            }

            static void Summary()
            {
                std::ostream &out = Output();
                out << "Tests: " << Total() << " | Passed: " << Passed() << " | Failed: " << Failed() << '\n';
            }

            static bool AllPassed()
            {
                return Failed() == 0;
            }

            static void Log(const std::string &text)
            {
                Output() << text << '\n';
            }

            static void Section(const std::string &name)
            {
                Output() << "== " << name << " ==" << '\n';
            }

        private:
            static inline std::size_t &Total()
            {
                static std::size_t total = 0;
                return total;
            }

            static inline std::size_t &Passed()
            {
                static std::size_t passed = 0;
                return passed;
            }

            static inline std::size_t &Failed()
            {
                static std::size_t failed = 0;
                return failed;
            }

            static inline bool &Verbose()
            {
                static bool verbose = true;
                return verbose;
            }

            static inline std::ostream &Output()
            {
                auto *ptr = OutputPtr();
                return ptr ? *ptr : std::cout;
            }

            static inline std::ostream *&OutputPtr()
            {
                static std::ostream *out = &std::cout;
                return out;
            }
        };
    }
}
