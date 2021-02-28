#include <utility>
#include "Sender.hxx"
#include "Receiver.hxx"
#include "Support/String.hxx"

using namespace Mud::Log;
namespace STR = Mud::Support::String;

//--- public constructors ---

Sender::Sender(const std::string &name)
: _receiver(Receiver::instance()), _component(name)
{
}

Sender::Sender(const Sender &rhs)
: _receiver(Receiver::instance()), _component(rhs._component)
{
}

Sender::Sender(Sender &&rhs)
: _receiver(Receiver::instance()), _component(std::move(rhs._component))
{
}

Sender::~Sender()
{
}

//--- public operators ---

Sender &Sender::operator=(const Sender &rhs)
{
    if (this != &rhs)
        _component = rhs._component;

    return *this;
}

Sender &Sender::operator=(Sender &&rhs)
{
    if (this != &rhs)
        _component = std::move(rhs._component);

    return *this;
}

//--- public methods ---

void Sender::setComponentName(const std::string &name)
{
    _component = name;
}

std::string Sender::componentName() const
{
    return _component;
}

void Sender::log(const std::string &message, const std::string &component,
                 const T::Timepoint &stamp, const Level level) const
{
    commit(level, stamp, component.empty() ? _component : component, std::move(STR::trim(message)));
}

void Sender::info(const std::string &message, const std::string &component,
                  const T::Timepoint &stamp) const
{
    commit(Level::Info, stamp, component.empty() ? _component : component,
           std::move(STR::trim(message)));
}

void Sender::warn(const std::string &message, const std::string &component,
                  const T::Timepoint &stamp) const
{
    commit(Level::Warn, stamp, component.empty() ? _component : component,
           std::move(STR::trim(message)));
}

void Sender::error(const std::string &message, const std::string &component,
                   const T::Timepoint &stamp) const
{
    commit(Level::Error, stamp, component.empty() ? _component : component,
           std::move(STR::trim(message)));
}

void Sender::fatal(const std::string &message, const std::string &component,
                   const T::Timepoint &stamp) const
{
    commit(Level::Fatal, stamp, component.empty() ? _component : component,
           std::move(STR::trim(message)));
}

void Sender::debug(const std::string &message, const std::string &component,
                   const T::Timepoint &stamp) const
{
    commit(Level::Debug, stamp, component.empty() ? _component : component,
           std::move(STR::trim(message)));
}

//--- protected methods ---

void Sender::commit(const Level level, const T::Timepoint &stamp, const std::string &component,
                    std::string &&message) const
{
    Entry entry{level, stamp, component, std::move(message)};

    _receiver.addEntry(std::move(entry));
}
