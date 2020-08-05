#!/usr/bin/python3

opcodes = {"LDI": 0b1111, "CMV":0b0000}
registers = 'ABCDEFGH'
registers = dict(zip(registers, [_ for _ in range(0, len(registers))]))

def createOperation(op):
    return opcodes[op] << 28

def toBinary(reg, pos):
    return registers[reg]<<pos

def tokenise(line):
    tokens = []
    for t in line.split():
        tokens.append("".join(t.strip()))
    return tokens

def parse(tokens):
        operation = opcodes[tokens[0]] << 28
        if tokens[0] == "LDI":
            a = registers[tokens[1]] << 21
            v = int(tokens[2])
            o = format(((operation | a) | v), '032b')
        else:
            a = registers[tokens[1]] << 6
            b = registers[tokens[2]] << 3
            c = registers[tokens[3]] 
            o = format((((operation | a) | b) | c), '032b')
        return o

def loadFile(filename):
    lines = []
    with open(filename, 'r') as f:
        for line in f:
            lines.append(tokenise(line))
    return lines

if __name__ == "__main__":
    raw = loadFile("asm.asm")
    asm = []
    for line in raw:
        asm.append(parse(line))
    print(asm) 

