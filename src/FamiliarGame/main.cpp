#include <FamiliarEngine/Filesystem/Serialization.hpp>

class Dog {
    std::string name = 0;
public:
    Dog(std::string _id) : name(_id) {};
};
int main()
{
    /*auto dog = new Dog();
    int* param = (int*)&dog->name;
    int* param2 = (int*)&"aaa";
    *param = *param2;
    sizeof(param);*/

    //ObjectID, ParamID, Value
    std::string name = "Bbb";
    auto record = FamiliarEngine::SerializableRecord("name", name.size(), &name[0]);
    std::ifstream fileStream("name.bin",
        std::ifstream::in
        | std::ifstream::binary);


    fileStream.clear();
    fileStream.close();
    system("pause");
    return 0;
}
