#ifndef BN_SRAM_H
#define BN_SRAM_H

#include <fstream>
#include <vector>
#include <iostream>

namespace bn::sram
{
    inline void read(void *destination, int size)
    {
        std::ifstream file("save.dat", std::ios::binary);
        if (file.is_open())
        {
            file.read(static_cast<char *>(destination), size);
            file.close();
        }
        else
        {
            // If no save file, clear memory to 0
            std::fill((char *)destination, (char *)destination + size, 0);
        }
    }

    inline void write(const void *source, int size)
    {
        std::ofstream file("save.dat", std::ios::binary);
        if (file.is_open())
        {
            file.write(static_cast<const char *>(source), size);
            file.close();
        }
    }
}

#endif