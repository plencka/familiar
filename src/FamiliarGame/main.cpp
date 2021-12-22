#include <FamiliarEngine/Serialization.hpp>

using namespace FamiliarEngine;
class Dog : public ISerializable {
    std::string name = "";
    int age = 0;
public:
    Dog(std::string _name, int _age) 
        : name(_name),
        age(_age){};

    virtual void serialize(SerializablePackage& package) override
    {
        package.insert(&name, "name");
        package.insert(&age, "age");
    }

    virtual void deserialize(SerializablePackage& package) override
    {
        package.retrieve(&age, "age");
        package.retrieve(&name, "name");
    }

    virtual std::string getFilename() override
    {
        return "Dog.bin";
    }

    virtual std::string getPath() override
    {
        return "";
    }
};

int main()
{
    Dog dog = Dog("bbb", 17);
    Deserializer(&dog).handle();
    system("pause");
    return 0;
}
