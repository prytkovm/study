#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

class RabinHash
{
public:
    size_t hash;
    RabinHash(std::string text, size_t key_size)
    {
        this->text = text;
        hash = 0;
        start = 0;
        end = key_size;
        this->key_size = key_size;
        length = text.length();
        for (size_t i = 0; i < key_size; i++)
            hash += (((size_t)text[i])) * ((size_t)(pow_m(37, key_size - i - 1)));
    }
    void move()
    {
        if (end <= (length - 1))
        {
            hash -= (((size_t)text[start])) * ((size_t)(pow_m(37, key_size - 1)));
            hash *= 37;
            hash += ((size_t)text[end]);
            start++;
            end++;
        }
    }
    std::string current_subsring()
    {
        std::string substr = "";
        for (int i = start; i < end; i++)
            substr += text[i];
        return substr;
    }
private:
    int length, start, end, key_size;
    const size_t MOD = 2e127 - 1;
    std::string text;
    size_t pow_m(size_t base, size_t power)
    {
        size_t result = 1;
        for (size_t i = 0; i < power; i++)
        {
            result = (result * base) % MOD;
        }
        return result;
    }
};

class TextSearch
{
public:
    TextSearch(std::string plainText)
    {
        this->plainText = plainText;
        length = plainText.length();
    }
    int search_KMP(std::string key)
    {
        std::vector<int> prefix = prefix_function(key);
        int key_length = key.length();
        int i = 0, j = 0;
        while (j < length)
        {
            if (key[i] == plainText[j])
            {
                i++;
                j++;
                if (i == key_length)
                    return j - key_length;
            }
             else if (i > 0)
                    i = prefix[i - 1];
             else
                j++;
        }
        return -1;
    }
    int search_BM(std::string key)
    {
        std::vector<int> prefix = prefixBM(key);
        int j, key_length = key.length();
        int offset = 0;
        while (offset <= (length - key_length))
        {
            j = key_length - 1;
            while (j >= 0 && key[j] == plainText[offset + j])
                --j;
            if (j < 0)
                return offset;
            else
                offset += std::max(1, j - prefix[plainText[offset + j]]);
        }
        return -1;
    }
    int search_Rab(std::string key)
    {
        RabinHash text_hash(plainText, key.length());
        RabinHash key_hash(key, key.length());
        for (int i = 0; i < (int)(length - key.length() + 1); i++)
        {
            if (text_hash.hash == key_hash.hash)
            {
                if (text_hash.current_subsring() == key)
                    return i;
            }
            text_hash.move();
        }
        return -1;
    }
private:
    std::string plainText;
    int length;
    std::vector<int> prefix_function(std::string text)
    {
        std::vector<int> prefix(text.length());
        int j = 0, i = 1;
        while (i < (int)text.length())
        {
            if (text[j] != text[i])
            {
                if (j > 0)
                    j = prefix[j - 1];
                else
                    i++;
            }
            else
            {
                prefix[i] = j + 1;
                ++i;
                ++j;
            }
        }
        return prefix;
    }
    std::vector<int> prefixBM(std::string text)
    {
        std::vector<int> prefix(256);
        for (int i = 0; i < 256; i++)
            prefix[i] = -1;
        for (int i = 0; i < (int)text.length(); i++)
        {
            prefix[(int)text[i]] = i;
        }
        return prefix;
    }
};
