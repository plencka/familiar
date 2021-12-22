#include <FamiliarEngine/Filesystem/Serialization.hpp>

using namespace FamiliarEngine;
class Dog : public ISerializable {
    std::string name = "Doggo";
    int age = 15;
public:
    Dog(std::string _name, int _age) : name(_name), age(_age){};

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
    Dog dog = Dog("Alfonso", 6666);
    Deserializer(&dog).handle();
    system("pause");
    return 0;
}
