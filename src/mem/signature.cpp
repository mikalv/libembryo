//
// libembryo
//
// Copyright Stanley Cen 2013
// Released under the MIT License
//

#include "signature.h"

#include <libembryo/logger.h>

#include <sstream>

namespace embryo
{
    signature::signature(std::string idapattern)
    {
        idapattern.erase(std::remove(idapattern.begin(), idapattern.end(), ' '), idapattern.end());
        for (auto it = idapattern.cbegin(); it != idapattern.cend();)
        {
            if (*it == '?')
            {
                m_pattern += '\0';
                m_mask += '?';
                ++it;
                continue;
            }
            std::stringstream converter(std::string(it, it + 2));
            unsigned short cur = 0;
            converter >> std::hex >> cur;
            unsigned char byteCur = static_cast<unsigned char>(cur);
            m_pattern += byteCur;
            m_mask += 'x';
            it += 2;
        }
    }

    signature::signature(const std::string& pattern, const std::string& mask) : m_pattern(pattern),
        m_mask(mask)
    {
    }
}