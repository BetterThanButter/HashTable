#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <limits.h>

#define HASH_NUM 30000

#define FILE_SIZE 150000000

using namespace std;
static unsigned int current_offset = HASH_NUM;
struct FileMapping {
    int fd;
    size_t fsize;
    unsigned int * valuesPtr;
    unsigned * dataPtr;

};

FileMapping * fileMappingCreate(const char* fname) {
    //open file
    int fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if(fd < 0) {
        cerr << "fileMappingCreate - open failed, fname =  " << fname << ", " << strerror(errno) << std::endl;
        return nullptr;
    }
    // установим размер файла
    int result = lseek(fd, FILE_SIZE, SEEK_CUR);
    if (result == -1) {

        close(fd);
        cerr << "Error calling lseek() to 'stretch' the file";
        return nullptr;
    }
    result = write(fd, "", 1);
    if (result < 0) {
        close(fd);
        cerr << "Error writing a byte at the end of the file";
        return nullptr;
    }
    //Узнаем размер файла
    struct stat st;
    if(fstat(fd, &st) < 0) {
        cerr << "fileMappingCreate - fstat failed, fname = " << fname << ", " << strerror(errno) << std::endl;
        close(fd);
        return nullptr;
    }

    size_t fsize = (size_t)st.st_size;

    //Вызовом mmap создаем отображение файла в память:
    unsigned int* dataPtr = (unsigned int*)mmap(nullptr, FILE_SIZE, PROT_READ | PROT_WRITE,  MAP_SHARED, fd, SEEK_SET);
    if(dataPtr == MAP_FAILED) {
        cerr << "fileMappingCreate - mmap failed, fname = " << fname << ", " << strerror(errno) << std::endl;
        close(fd);
        return nullptr;
    }
    // место под таблтцу , адреса будем хранить интами
    memset(dataPtr, 0, HASH_NUM );
//    Наконец, заполняем структуру FileMapping и возвращаем указатель на нее в качестве результата:

    FileMapping * mapping = (FileMapping *)malloc(sizeof(FileMapping));
    if(mapping == nullptr) {
        cerr << "fileMappingCreate - malloc failed, fname = " << fname << std::endl;
        munmap(dataPtr, fsize);
        close(fd);
        return nullptr;
    }

    mapping->fd = fd;
    mapping->fsize = fsize;
    mapping->dataPtr = dataPtr;
   // mapping->valuesPtr = dataPtr + HASH_NUM * sizeof(unsigned int);

    return mapping;
}

void fileMappingClose(FileMapping * mapping) {
    munmap(mapping->dataPtr, mapping->fsize);
    close(mapping->fd);
    free(mapping);
}
unsigned int* fileMappingGetPointer(FileMapping * mapping) {
    return mapping->dataPtr;
}
unsigned int fileMappingGetSize(FileMapping * mapping) {
    return (unsigned int)mapping->fsize;
}

unsigned int myHash (const string line) {
    //cout << "hash : ";
    const int p = 31;
    const char * s = line.c_str();
    unsigned long length = line.length();
    unsigned int hash = 0, p_pow = 1;
    for (size_t i = 0; i < length; ++i)
    {
        // желательно отнимать 'a' от кода буквы
        // единицу прибавляем, чтобы у строки вида 'aaaaa' хэш был ненулевой
        hash += (s[i] - 'a' + 1) * p_pow;
        p_pow *= p;
    }
    return hash % HASH_NUM;
}

int ADD(const string key, const string value);
int DELETE(const string key);
int PRINT(const string key);
//void UPDATE(string key);

const char * filepath = "storage1";
FileMapping * mymap = fileMappingCreate(filepath);

//укажем на места для данных

int main() {

    int n;
    scanf("%d\n", &n);
    string command;
    vector <string> args;
    string key, value;

    for(int i = 0; i < n; i++) {
        cin >> command;
        cin >> key;

        if(command == "ADD"){
            cin >>  value;
            int kek = ADD(key, value);
            if (kek < 0)
                cout << "ERROR\n";
        }
        if(command == "UPDATE"){
            cin >> value;
            if(DELETE(key) < 0 or ADD(key, value) < 0) {
                cout << "ERROR\n";
            }

        }
        if(command == "DELETE"){

            int hh = DELETE(key);
            if(hh < 0)
                cout << "ERROR\n";
        }
        if(command == "PRINT"){
            int lol = PRINT(key);
            if(lol < 0)
                cout << "ERROR\n";
        }
        else {
            continue;
        }
    }

    fileMappingClose(mymap);
    remove(filepath);
//    if( remove(filepath) != 0 )
//        perror( "Error deleting file" );
//    else
//        puts( "File successfully deleted" );

    return  0;
}

int ADD(const string key, const string value) {


    unsigned * current_address = mymap->dataPtr + (size_t) myHash(key) % HASH_NUM;

    // если что то еще есть
    while(*current_address != 0) {
        //если неравно нулю
        //в current_address сейчас лежим сдвиг на первый пустой
        //если до этого было 0 то там offset
        current_address = mymap->dataPtr + *current_address;
  //      cout << "current_address (if!=0) begin: " << current_address << endl;
        unsigned int key_len = *current_address;
        current_address += 3;
   //     cout << "current_address (if!=0) key_addr: " << current_address << endl;
        //вытаскиваем ключ
        char * current_key = new char[key_len + 1];
        memcpy(current_key, current_address, key_len);
        current_key[key_len] = '\0';

        if (strcmp(key.c_str(), current_key) == 0) {
            // cout << "ERROR\n";
            return -1;
        }
        current_address-= 1;
 //       cout << "current_address (return to nexaddr: " << current_address << endl;
    }

    // в адрес положили сдвиг на новое пустое место
    *current_address = current_offset;
 //   cout << "current_address with offset: " << current_address << endl;

    //передвинули головку на пустое место
    current_address = mymap->dataPtr + current_offset;

    //сейчас займем место, поэтому увеличим адрес нового места
    current_offset += 5  + key.size() / sizeof(unsigned int) + value.size() / sizeof(unsigned int) ;
  //  cout << "current offset: " << current_offset << endl;

    *current_address = key.size();
    //unsigned int *pcontent = current_address;
    //unsigned int content = *pcontent;
    //  printf("Address key.size() %p: content %08x\n", pcontent, content);
    current_address++;
//    cout << "current_address on size2: " << current_address << endl;

    //запишем размер value
    *current_address = value.size();
//    pcontent = current_address;
//    content = *pcontent;
    //   printf("Address val.size() %p: content %08x\n", pcontent, content);
    current_address++;
 //   cout << "current_address on newaddr: " << current_address << endl;

    //выделим место для адреса перехода
    *current_address = 0;
//    pcontent = current_address;
//    content = *pcontent;
    //   printf("Address next.add() %p: content %08x\n", pcontent, content);
    current_address++;
 //   cout << "current_address on key: " << current_address << endl;
    //           запишем строчку нашу
    memcpy(current_address, key.c_str(), key.size());
    memcpy(current_address + 1 + key.size() / 4, value.c_str(), value.size());
 //  printf("key: %s value: %s\n", current_address, current_address + 1 + key.size() / 4);
    return  0;


}
int DELETE(string key) {

    unsigned *current_address = mymap->dataPtr + (size_t) myHash(key) % HASH_NUM;

    unsigned *previous = current_address;

    //пройдем до конца
    while(*current_address != 0)
    {
        current_address = mymap->dataPtr + *current_address;
        unsigned int key_len = *current_address;

        //jumo to key
        current_address += 3;
        //  printf("key: %s value: %s\n",current_address, current_address + key.size());
        char * current_key = new char[key_len + 1];
        memcpy(current_key, current_address, key_len);
        current_key[key_len] = '\0';

        //вернем на аддрес
        current_address--;
        if (strcmp(key.c_str(), current_key) == 0)
        {
            *previous = *current_address;
            //     cout << "SUCCESS\n";
            delete [] current_key;
            return 0;
        }
        delete [] current_key;

        previous = current_address;
    }
    //  cout << "ERROR\n";
    return -1;
}
int PRINT(const string key){

    unsigned *current_address = mymap->dataPtr +  (size_t) myHash(key) % HASH_NUM;
// если там не ноль - круто
    while(*current_address != 0)
    {
        //берем адрес который там лежит (разименуем cuurent addredd)
        current_address = mymap->dataPtr + *current_address;

        unsigned key_length = *current_address;
        current_address++;
       // cout << key_length << endl;

        unsigned value_length = *current_address;
        //cout << value_length << endl;
        current_address += 2;

        char * key_str = new char[key_length + 1];
        char * value_str = new char[value_length + 1];

       // printf("key: %s value: %s\n", current_address, current_address + key.size() + 1);
        memcpy(key_str, current_address, key_length);
       // current_address++;
        memcpy(value_str, key_length/4 + 1 + current_address, value_length);
        // вернем на адрес следующего элемента(если он есть)
        current_address -= 1;
        //cout << *current_address;
        key_str[key_length] = '\0';
        value_str[value_length] = '\0';

        if (strcmp(key.c_str(), key_str) == 0) {
            printf("%s %s\n", key_str, value_str);
            delete [] key_str;
            delete [] value_str;
            return 0;
        }
        delete [] key_str;
        delete [] value_str;
    }
// есть ли ноль = пусто(
    // cout << "ERROR\n";
    return -1;
}