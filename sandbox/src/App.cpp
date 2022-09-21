#include "hzpch.h"
#include "../../lib/src/hazel.h"
class Sandbox : public Hazel::Application {
public:
    Sandbox() {
    }

    ~Sandbox() {
    }
};

Hazel::Application *Hazel::CreateApplication() {
    auto toRet = new Sandbox();
    if (toRet == nullptr) {
        Logger::Error("couldn't create %s object", typeid(toRet).name());
    }
    Logger::Info("succesfully created %s object, at 0x%p", typeid(toRet).name(), toRet);
    return toRet;
}
