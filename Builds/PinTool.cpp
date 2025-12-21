#include "pin.H"
#include <iostream>
#include <fstream>

// Output file
std::ofstream outFile;

unsigned int c = 0;
// This function is called before every memory read
VOID RecordMemRead(VOID *ip, VOID *addr)
{
    outFile << c++ << "\tread\t" << addr << std::endl;
}

// This function is called before every memory write
VOID RecordMemWrite(VOID *ip, VOID *addr)
{
    outFile << c++ << "\twrite\t" << addr << std::endl;
}

// This function is called for every instruction
VOID Instruction(INS ins, VOID *v)
{
    // Instrument memory reads
    if (INS_IsMemoryRead(ins))
    {
        INS_InsertPredicatedCall(
            ins, IPOINT_BEFORE, (AFUNPTR)RecordMemRead,
            IARG_INST_PTR,
            IARG_MEMORYREAD_EA,
            IARG_END);
    }

    // Instrument memory writes
    if (INS_IsMemoryWrite(ins))
    {
        INS_InsertPredicatedCall(
            ins, IPOINT_BEFORE, (AFUNPTR)RecordMemWrite,
            IARG_INST_PTR,
            IARG_MEMORYWRITE_EA,
            IARG_END);
    }
}

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    outFile.close();
}

// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char *argv[])
{
	std::string tracename = "Trace.stl";
    // Initialize pin
    if (PIN_Init(argc, argv))
    {
        std::cerr << "This Pintool records memory read and write traces" << std::endl;
        return 1;
    }

    // Open the output file
    outFile.open(tracename);

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}
