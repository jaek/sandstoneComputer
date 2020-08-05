#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define NUM_R 8
#define MAX_PROGRAM_SIZE 1000

#define OP_MASK 0xF0000000
#define L_MASK 0x0E000000
#define A_MASK 0x1C0
#define B_MASK 0x038
#define C_MASK 0x007

class Machine{
    private:
    uint32_t r[NUM_R];
    uint32_t pm[MAX_PROGRAM_SIZE];
    int pm_length = 0;
    public:
    void load_r(int reg, char data);
    void init_r();
    void dump_r();
    void load_program();
    void read_program_file(string filename);
    void dump_program_memory();
    void parse_instruction(uint32_t instruction);
};

// Register methods
void Machine::init_r(){
    for(int i = 0; i < NUM_R; i++){
        r[i] = 0;
    }
};

void Machine::dump_r(){
    char c = 'A';
    for(int i = 0; i < NUM_R; i++){
        cout << c << " " << r[i] << "\n";
        c++;
    }
    cout << "\n";
};

void Machine::load_r(int reg, char data){
    r[reg] = data;
}

// Load program

void Machine::read_program_file(string filename){
    int i = 0;
    pm_length = 0;
    std::ifstream infile(filename);
    while(i < MAX_PROGRAM_SIZE && infile >> pm[i]){
        i++;
        pm_length++;
    }
};

void Machine::dump_program_memory(){
    int i = 0;
    cout << "Program contents:\n";
    while(i < MAX_PROGRAM_SIZE && i < pm_length){
        cout << pm[i] << "\n";
        i++;
    }
    cout << "\n";
};

// Operations

void Machine::parse_instruction(uint32_t instruction){
    short opcode = (instruction & OP_MASK) >> 28;
    short a = (instruction & A_MASK) >> 6;
    short b = (instruction & B_MASK) >> 3;
    short c = (instruction & C_MASK);
    cout << " OPCODE: " << opcode << " A " << a << " B " << b << " C " << c << "\n";
    switch(opcode){

        case 0b1111:
            a = (instruction & L_MASK) >> 25;
            r[a] = ~(OP_MASK | L_MASK) & instruction; //load the least significant 25 bits into register 'a'
            cout << "A :"<< r[a] << '\n';

        // The register A receives the value in register B, unless the register C contains 0.
        case 0b0000 :  
            if (r[c] != 0){
                r[a] = r[b];
            }
            break;

        //  The register A receives the value stored at offset C in the array identified by B.
        case 1 : 
            break;

        //  The array identified by A is amended at the offset in register B to store the value in register C.
        case 2 : 
            break;
        case 11:

            break;
    };
}

//main loop
int main(){
    Machine r;
    r.init_r();
    r.dump_r();
    r.read_program_file("test.txt");
    r.dump_program_memory();
    r.parse_instruction(0b11110000000000000000000001100100);
    r.parse_instruction(0b00000000000000000000000001000000);
    r.dump_r();
}
