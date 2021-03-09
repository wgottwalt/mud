#pragma once

#include "Defaults.hxx"

namespace Mud::Log
{
    namespace T = Mud::Support::Time;

    class Receiver;

    class Sender {
    public:
        //--- public constructors ---
        Sender(const std::string &name = "undef");
        Sender(const Sender &rhs);
        Sender(Sender &&rhs) noexcept;
        virtual ~Sender() noexcept;

        //--- public operators ---
        Sender &operator=(const Sender &rhs);
        Sender &operator=(Sender &&rhs) noexcept;

        //--- public methods ---
        void setComponentName(const std::string &name);
        std::string componentName() const;
        void log(const std::string &message, const std::string &component = "",
                 const T::Timepoint &stamp = T::now(), const Level level = Level::Debug) const;
        void info(const std::string &message, const std::string &component = "",
                  const T::Timepoint &stamp = T::now()) const;
        void warn(const std::string &message, const std::string &component = "",
                  const T::Timepoint &stamp = T::now()) const;
        void error(const std::string &message, const std::string &component = "",
                   const T::Timepoint &stamp = T::now()) const;
        void fatal(const std::string &message, const std::string &component = "",
                   const T::Timepoint &stamp = T::now()) const;
        void debug(const std::string &message, const std::string &component = "",
                   const T::Timepoint &stamp = T::now()) const;

    protected:
        //--- protected methods ---
        void commit(const Level level, const T::Timepoint &stamp, const std::string &component,
                    std::string &&message) const;

    private:
        //--- private properties ---
        Receiver &_receiver;
        std::string _component;
    };
}
