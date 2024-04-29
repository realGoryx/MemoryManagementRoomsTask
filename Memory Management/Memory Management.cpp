#include <iostream>

#define MAXIMUM_ROOMS 100


struct Person {
    char name[1000];
    int number_keys = 0;
};


struct Room {
    int id_number;
    Person* person;
};


static void errorMessage();

static void readRooms(Room* rooms, int numberRooms){

    std::cout << "LOG:\n";

    for (int i = 0; i < numberRooms; ++i) {

        std::cout << "Room " << rooms[i].id_number << ": ";

        if (rooms[i].person == nullptr)
            std::cout << " - \n";
        else
            std::cout << rooms[i].person->name << ", keys: " << rooms[i].person->number_keys << "\n";

    }

}


static void giveRoomD(int index, char* name, Room* rooms) {


    Person* person = new Person;

    strcpy_s(person->name, name);

    person->number_keys += 1;


    if (rooms[index].person != nullptr) {
        if (rooms[index].person->number_keys == 0) {
            delete rooms[index].person;
        }
    }

    rooms[index].person = person;

}


static void giveRoomB(int index, int id, Room* rooms, int numberOfRooms) {


    bool exist = false;

    for (int i = 0; i < numberOfRooms; ++i) {
        if (id == rooms[i].id_number)
            exist = true;
        if (i == numberOfRooms - 1) {
            exist = false;
        }
    }

    if (index <= numberOfRooms - 1)
        exist = true;
    else
        exist = false;

    if (rooms[index].person == nullptr)
        exist = false;


    if (!exist) {
        errorMessage();
        return;
    }


    if (rooms[index].person != nullptr) {
        exist = true;
        rooms[index].person->number_keys += 1;

        Person* person = rooms[index].person;

        for (int i = 0; i < numberOfRooms; ++i) {
            if (id == rooms[i].id_number) {
                if(rooms[i].person != nullptr)
                    rooms[i].person->number_keys -= 1;

                rooms[i].person = person;
                break;
            }
        }


    }

}


static void errorMessage() {
    std::cout << "!\n";
}


int main()
{
    int number_rooms;
    Room rooms[MAXIMUM_ROOMS];

    std::cin >> number_rooms;

    for (int i = 0; i < number_rooms; ++i) {
        std::cin >> rooms[i].id_number;
        rooms[i].person = nullptr;
    }

    bool quit = false;

    int indexNumber;

    while (!quit) {
        char key;
        std::cin >> key;

        switch (key) {
        case 'D':
            std::cin >> indexNumber;

            char name[1000];
            std::cin >> name;

            giveRoomD(indexNumber, name, rooms);

            break;
        case 'B':
            std::cin >> indexNumber;

            int idNumber;
            std::cin >> idNumber;

            giveRoomB(indexNumber, idNumber, rooms, number_rooms);
            break;
        case 'P':
            readRooms(rooms, number_rooms);
            break;
        case 'Q':
            quit = true;
            break;
        }
    }
    
    return 0;
}
