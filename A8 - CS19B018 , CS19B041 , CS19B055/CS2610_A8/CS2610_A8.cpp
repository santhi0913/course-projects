#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <pthread.h>
#include <cstdlib>
#include <bits/stdc++.h>
#include <thread>
#include <unistd.h>
#include <queue>

using namespace std;

ofstream out("Output.txt");
ofstream dcacheOut("DC.txt");
ifstream MyFile("ICache.txt");
ifstream File("DCache.txt");
ifstream registerF("RF.txt");

int *HexToBin(string hexdec)
{
    string dec;
    char HexDec[2];
    HexDec[0] = hexdec[0];
    HexDec[1] = hexdec[1];

    for (int i = 0; i < 2; i++)
    {
        switch (HexDec[i])
        {
        case '0':
            dec += "0000";
            break;
        case '1':
            dec += "0001";
            break;
        case '2':
            dec += "0010";
            break;
        case '3':
            dec += "0011";
            break;
        case '4':
            dec += "0100";
            break;
        case '5':
            dec += "0101";
            break;
        case '6':
            dec += "0110";
            break;
        case '7':
            dec += "0111";
            break;
        case '8':
            dec += "1000";
            break;
        case '9':
            dec += "1001";
            break;
        case 'A':
        case 'a':
            dec += "1010";
            break;
        case 'B':
        case 'b':
            dec += "1011";
            break;
        case 'C':
        case 'c':
            dec += "1100";
            break;
        case 'D':
        case 'd':
            dec += "1101";
            break;
        case 'E':
        case 'e':
            dec += "1110";
            break;
        case 'F':
        case 'f':
            dec += "1111";
            break;
        default:
            break;
        }
    }

    int *bin;
    bin = new int[2 * 4];
    for (int i = 0; i < 2 * 4; i++)
    {
        if (dec[i] == '1')
            bin[i] = 1;
        else
            bin[i] = 0;
    }

    return bin;
}

int binaryToDecimal2(int *instruction, int length)
{
    int power = pow(2, length - 1);
    int sum = 0;
    int i;

    for (i = 0; i < length; ++i)
    {
        if (i == 0 && instruction[i] != 0)
        {
            sum = power * -1;
        }
        else
        {
            sum += (instruction[i]) * power; //The -0 is needed
        }
        power /= 2;
    }

    return sum;
}

int hexToDecimal(char s)
{

    int dec_val = 0;
    if (s >= '0' && s <= '9')
    {
        dec_val += (s - 48);
        // incrementing base by power
    }

    // if character lies in 'A'-'F' , converting
    // it to integral 10 - 15 by subtracting 55
    // from ASCII value
    else if (s >= 'a' && s <= 'f')
    {
        dec_val += (s - 87);
        // incrementing base by power
    }

    return dec_val;
}

int dest;
int IR[4];
bool halt;
int ALUOutput;
int PC;
int curPC;
int LMD;
int RF[16];
int registrFile[16];
int instructions[128][4];
char L1[128][2];
char L2[128][2];
int data[256];
bool memRef, alu, branch;
int opCode, r1, r2;
int validRegister[16];
int validStage[5];
int Op[5];
bool ignoreF = false;
int Stall = 0;
int Total_Clock_Cycles = 0;
int InvalidFetch = 0;
int Tot_Ins = 0;
int Ari_Ins = 0;
int Log_Ins = 0;
int Data_Ins = 0;
int Con_Ins = 0;
int Hal_Ins = 0;
double CPI = 0;
int R_destination[5];
int Tot_Stalls = 0;
int Data_Stalls = 0;
int Con_Stalls = 0;
int stallCont = 0;
int OpCodeEX, OpCodeMem, OpCodeWB, PCId, PCEx, ALUWb, ALUMem, destID, destEX, destMem, destWB;
bool idflag = false, ifflag = false, exflag = false, memflag = false, wbflag = false;
int Condition_BEQZ = 0;
void ScalarPipeline(string ICache[128], string DCache[256], string RegisterFile[16])
{
    for (int i = 0; i < 16; i++)
    {
        int *bin = HexToBin(RegisterFile[i]);
        RF[i] = binaryToDecimal2(bin, 8);
        validRegister[i] = 1;
    }

    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int decI = hexToDecimal(ICache[i][j]);

            instructions[i][j] = decI;
        }

        for (int j = 0; j < 2; j++)
        {
            L1[i][j] = ICache[i][j + 1];
            L2[i][j] = ICache[i][j + 2];
        }
    }
    for (int i = 0; i < 256; i++)
    {
        // for considering 2's complement too
        int *binD = HexToBin(DCache[i]);
        int decD = binaryToDecimal2(binD, 8);
        data[i] = decD;
    }

    PC = 0;
    memRef = false;
    alu = false;
    branch = false;
    halt = false;
}
int readRF(int x)
{

    return RF[x];
}
void Fetch()
{

    for (int i = 0; i < 4; i++)
    {
        IR[i] = instructions[PC][i];
    }
    curPC = PC;
    PC += 1;
    Op[0] = IR[0];
}
void ID()
{

    PCId = PC;
    dest = IR[1];
    destID = dest;
    int A, B, R_2;
    int X;
    string s1, s2;
    s1 = L1[curPC];
    s2 = L2[curPC];
    int *q1 = HexToBin(s1);
    int *q2 = HexToBin(s2);

    int l1 = binaryToDecimal2(q1, 8);
    int l2 = binaryToDecimal2(q2, 8);

    switch (IR[0])
    {
    case 0:

        if (validRegister[IR[2]] && validRegister[IR[3]])
        {
            idflag = true;
            A = readRF(IR[2]);
            B = readRF(IR[3]);
            alu = true;
            opCode = 0;
            r1 = A;
            r2 = B;
            validRegister[IR[1]] = 0;
            Stall = 0;
        }
        else if (!validRegister[IR[2]] || !validRegister[IR[3]])
        {
            idflag = false;
            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        break;
    case 1:

        if (validRegister[IR[2]] && validRegister[IR[3]])
        {
            A = readRF(IR[2]);
            B = readRF(IR[3]);
            alu = true;
            opCode = 1;
            r1 = A;
            r2 = B;
            validRegister[IR[1]] = 0;
            Stall = 0;
        }
        else if (!validRegister[IR[2]] || !validRegister[IR[3]])
        {
            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        break;
    case 2:

        if (validRegister[IR[2]] && validRegister[IR[3]])
        {
            A = readRF(IR[2]);
            B = readRF(IR[3]);
            alu = true;
            opCode = 2;
            r1 = A;
            r2 = B;
            validRegister[IR[1]] = 0;
            Stall = 0;
        }
        else if (!validRegister[IR[2]] || !validRegister[IR[3]])
        {
            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        break;
    case 3:

        if (validRegister[IR[1]])
        {
            A = readRF(IR[1]);
            alu = true;
            opCode = 3;
            r1 = A;
            r2 = 0;
            Stall = 0;
            validRegister[IR[1]] = 0;
        }
        else if (!validRegister[IR[1]])
        {
            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        break;
    case 4:

        if (validRegister[IR[2]] && validRegister[IR[3]])
        {
            A = readRF(IR[2]);
            B = readRF(IR[3]);
            alu = true;
            opCode = 4;
            r1 = A;
            r2 = B;
            validRegister[IR[1]] = 0;
            Stall = 0;
        }
        else if (!validRegister[IR[2]] || !validRegister[IR[3]])
        {
            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        break;
    case 5:

        if (validRegister[IR[2]] && validRegister[IR[3]])
        {
            A = readRF(IR[2]);
            B = readRF(IR[3]);
            alu = true;
            opCode = 5;
            r1 = A;
            r2 = B;
            validRegister[IR[1]] = 0;
            Stall = 0;
        }
        else if (!validRegister[IR[2]] || !validRegister[IR[3]])
        {
            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        break;
    case 6:

        if (validRegister[IR[2]] && validRegister[IR[3]])
        {
            A = readRF(IR[2]);
            alu = true;
            opCode = 6;
            r1 = A;
            r2 = 0;
            validRegister[IR[1]] = 0;
            Stall = 0;
        }
        else if (!validRegister[IR[2]] || !validRegister[IR[3]])
        {

            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        break;
    case 7:

        if (validRegister[IR[2]] && validRegister[IR[3]])
        {
            A = readRF(IR[2]);
            B = readRF(IR[3]);
            alu = true;
            opCode = 7;
            r1 = A;
            r2 = B;
            validRegister[IR[1]] = 0;
            Stall = 0;
        }
        else if (!validRegister[IR[2]] || !validRegister[IR[3]])
        {

            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        break;
    case 8:

        if (validRegister[IR[2]])
        {
            R_2 = readRF(IR[2]);
            X = IR[3];
            memRef = true;
            opCode = 8;
            r1 = R_2;
            r2 = X;
            validRegister[IR[1]] = 0;
            Stall = 0;
        }
        else if (!validRegister[IR[2]])
        {

            Stall = 1;
            Data_Stalls += 2;
            return;
        }

        break;
    case 9:

        if (validRegister[IR[2]])
        {
            R_2 = readRF(IR[2]);
            X = IR[3];
            memRef = true;
            opCode = 9;
            r1 = R_2;
            r2 = X;
            Stall = 0;
        }
        else if (!validRegister[IR[2]])
        {

            Stall = 1;
            Data_Stalls += 2;
            return;
        }

        break;
    case 10:
        branch = true;
        stallCont = 2;
        opCode = 10;
        r1 = l1;
        r2 = 0;
        Con_Stalls += 2;
        return;
        break;
    case 11:
        if (!validRegister[IR[1]])
        {

            Stall = 1;
            Data_Stalls += 2;
            return;
        }
        A = readRF(IR[1]);
        branch = true;
        opCode = 11;
        r1 = A;
        r2 = l2;
        stallCont = 2;
        Con_Stalls += 2;
        return;
        break;
    case 15:
        Hal_Ins++;
        halt = true;
        InvalidFetch = 1;
        opCode = 15;
        r1 = 0;
        r2 = 0;
        break;

    default:
        break;
    }
}

void Execute()
{

    OpCodeEX = opCode;
    PCEx = PCId;
    destEX = destID;
    if (OpCodeEX >= 0 && OpCodeEX <= 3)
        Ari_Ins++;
    if (OpCodeEX >= 4 && OpCodeEX <= 7)
        Log_Ins++;
    if (OpCodeEX >= 8 && OpCodeEX <= 9)
        Data_Ins++;
    if (OpCodeEX >= 10 && OpCodeEX <= 11)
        Con_Ins++;
    if (OpCodeEX == 15)
        Hal_Ins++;

    switch (OpCodeEX)
    {
    case 0:
        ALUOutput = r1 + r2;
        break;
    case 1:
        ALUOutput = r1 - r2;
        break;
    case 2:
        ALUOutput = r1 * r2;
        break;
    case 3:
        ALUOutput = r1 + 1;
        break;
    case 4:
        ALUOutput = r1 & r2;
        break;
    case 5:
        ALUOutput = r1 | r2;
        break;
    case 6:
        ALUOutput = ~r1;
        break;
    case 7:
        ALUOutput = r1 ^ r2;
        break;

    default:
        break;
    }
    if (OpCodeEX == 8 || OpCodeEX == 9)
    {
        ALUOutput = r1 + r2;
    }
    if (OpCodeEX == 10)
    {

        ALUOutput = PCEx + r1;
    }
    if (OpCodeEX == 11)
    {

        if (r1 == 0)
        {

            ALUOutput = PCEx + r2;
        }
        else
        {
            ALUOutput = PCEx;
        }
    }

    if (OpCodeEX == 15)
    {
        halt = true;
        InvalidFetch = 1;
        return;
    }
}

void MEM()
{
    OpCodeMem = OpCodeEX;
    ALUMem = ALUOutput;
    destMem = destEX;
    if (OpCodeMem == 8)
    {
        LMD = data[ALUMem];
    }
    if (OpCodeMem == 9)
    {
        data[ALUMem] = readRF(destMem);
    }
    if (OpCodeMem == 15)
    {
        halt = true;
        InvalidFetch = 1;
    }
}
void writeRF(int x, int data)
{

    RF[x] = data;
}
void writeBack()

{
    OpCodeWB = OpCodeMem;
    ALUWb = ALUMem;
    destWB = destMem;

    if (OpCodeWB < 8)
    {
        writeRF(destWB, ALUWb);
        validRegister[destWB] = 1;
    }
    else if (OpCodeWB == 8)
    {
        writeRF(destWB, LMD);
        validRegister[destWB] = 1;
    }
    if (OpCodeWB == 15)
    {
        halt = true;
    }
}

int main()
{
    string ICache[128];
    string DCache[256];
    string RegisterFile[16];
    string line1, line2;
    int i = 0;

    while (getline(MyFile, line1) && getline(MyFile, line2))
    {
        ICache[i] = line1 + line2;
        i++;
    }
    i = 0;

    while (getline(File, line1))
    {
        DCache[i] = line1;
        i++;
    }

    i = 0;

    while (getline(registerF, line1))
    {
        RegisterFile[i] = line1;
        i++;
    }

    ScalarPipeline(ICache, DCache, RegisterFile);
    i = 0;

    queue<int> if1, id, ex, mem, wb;
    if1.push(1);
    Fetch();

    while (!halt)
    {

        if (!mem.empty())
        {
            mem.pop();
            wb.push(1);
            writeBack();
        }
        if (!ex.empty())
        {
            ex.pop();
            mem.push(1);
            MEM();
        }
        if (!id.empty())
        {
            id.pop();
            ex.push(1);
            Execute();
        }
        if (!if1.empty())
        {
            if1.pop();
            id.push(1);
            ID();

            if (stallCont)
            {
            }
            else if (!Stall)
            {
                if1.push(1);
                Fetch();
            }
            else
            {
                id.pop();
            }
        }
        if (!stallCont && if1.empty() && id.empty() && ex.empty() && mem.empty())
        {
            if1.push(1);
            Stall = 0;
        }
        if (stallCont == 2 && id.empty() && if1.empty() && mem.empty() && !ex.empty())
        {
            if1.push(1);
            PC = ALUOutput;

            Fetch();
            stallCont = 0;
        }
        if (halt)
        {

            break;
        }
        Total_Clock_Cycles++;
    }
    Tot_Ins = Ari_Ins + Con_Ins + Log_Ins + Data_Ins + Hal_Ins;
    Tot_Stalls = Data_Stalls + Con_Stalls;

    out << "Total number of instructions executed  : " << Tot_Ins << endl;

    out << "Number of instructions in each class" << endl;
    out << "Arithmetic instructions\t\t: " << Ari_Ins << endl;
    out << "Logical instructions\t\t: " << Log_Ins << endl;
    out << "Data instructions\t\t\t: " << Data_Ins << endl;
    out << "Control instructions\t\t: " << Con_Ins << endl;
    out << "Halt instructions\t\t\t: " << Hal_Ins << endl;

    if (Tot_Ins != 0)
        CPI = (double)(Total_Clock_Cycles + 4) / Tot_Ins;
    else
        CPI = -1;

    out << "Cycles Per Instruction\t\t: " << CPI << endl;

    out << "Total number of stalls\t\t: " << Tot_Stalls << endl;
    out << "Data stalls (RAW)\t\t\t: " << Data_Stalls << endl;
    out << "Control stalls\t\t\t: " << Con_Stalls << endl;

    for (int i = 0; i < 256; i++)
    {
        if (data[i] < 0)
            data[i] += 256;
        char ch1 = data[i] / 16 + '0';
        char ch2 = data[i] % 16 + '0';

        if (ch1 > '9')
            ch1 = ch1 - '9' - 1 + 'a';
        if (ch2 > '9')
            ch2 = ch2 - '9' - 1 + 'a';

        dcacheOut << ch1 << ch2 << endl;
    }

    dcacheOut.close();
    out.close();
    registerF.close();
    File.close();
    MyFile.close();
    return 0;
}
