//
//  A1.cpp
//  Assignment 1
//
//  Created by Joy Mugo (MUGJD2103) on 13/10/2022.
//

#include <iostream>

using namespace std;

class String
{
public:

    String();
    String(const char*);
    String(const String&); //copy constructor

    bool empty() const;
    int length() const;
    String upper() const;
    int position(char) const;
    String substr(int,int) const;
    int substring(const String) const;

    String& operator= (const String); //assignment operator

    bool operator== (const char*);
    char& operator[](int) const;
    String& operator+= (char);
    String& operator+= (String);

    friend ostream& operator<< (ostream& outs , const String);
    friend bool operator== (const String , const String) ;
    friend String operator+ (const String& , const String& );
    int compareStrings(const String&, const String&) ;
    String reversedString (const String&) ;

    ~String(); //destructor

private:
    char* str;
    int len;

};

String::String()
{
    len = 0;
    str = nullptr;
}

String::String(const char* s)
{
    int count = 0;
    while (s[count] != '\0' )
        count++;
    len = count;
    str = new char[len];

    for ( int i = 0 ; i < len ; i++ )
        str[i] = s[i];
}

String::String(const String &s1)
{
    len = s1.len;
    str = new char[len];
    for ( int i = 0 ; i < len ; i++ )
        str[i] = s1.str[i];
}

bool String::empty() const
{
    if (len == 0)
        return true;
    return false;
}

int String::length() const
{
    return len;
}

String String::upper() const
{
    String temp;
    temp.len = len;
    temp.str = new char [temp.len];

    for ( int i = 0 ; i < len ; i++ )
    {
        if ( str[i] >= 'a' &&  str[i] <= 'z')
            temp.str[i] = str[i] - 32;
        else
            temp.str[i] = str[i];
    }

    return temp;
}

int String::position(char find) const
{
    for ( int i = 0 ; i < len ; i++ )
        if ( str[i] == find )
            return i;
    return -1;
}

String String::substr(int start ,int size) const
{
    String temp;
    if ( start >= len )
        return temp;

    if ( (size - start) > len)
        temp.len = len - start;
    else
        temp.len = size;

    temp.str = new char [temp.len];

    for ( int i = 0 , j = start ; i < temp.len ; i++ , j++)
        temp[i] = str[j];

    return temp;
}

int String::substring(const String s) const
{
    if ( s.len == 0)
        return 0;

    int check,index;
    for ( int i = 0 ; i < len ; i++)
    {
        check = 0;
        index = i;
        if (str[i] == s.str[0])
            for ( int j = 0, k = i  ; j < s.len ; j++,k++)
            {
                if ( str[k] == s.str[j])
                {
                    check++;
                    if ( check == s.len)
                        return index;
                }
                else
                    break;
            }
    }
    return -1;
}

String& String::operator= ( const String s1)
{
    if ( str == 0 )
        str = new char[s1.len];

    if ( len <= s1.len)
    {
        delete[] str;
        str = new char[s1.len];
    }
    len = s1.len;
    for ( int i = 0 ; i < len ; i++ )
        str[i] = s1.str[i];

    return *this;
}

bool operator== (const String str1 , const String str2)
{
    if ( str1.len != str2.len )
        return false;

    for ( int i = 0 ; i < str1.len ; i++ )
        if ( str1.str[i] != str2.str[i])
            return false;
    return true;
}

bool String::operator== (const char* s)
{
    String temp = s;

    if ( temp.len != len )
        return false;

    for ( int i = 0 ; i < len ; i++ )
        if ( temp.str[i] != str[i])
            return false;
    return true;
}

char& String::operator[](int i) const
{
    return str[i];
}

String operator+ ( const String& s1 , const String& s2)
{
    if ( s1.len == 0 )
        return s2;
    else if ( s2.len == 0 )
        return s1;

    String temp;
    temp.len = s1.len + s2.len;
    temp.str = new char [temp.len];

    int i;
    for ( i = 0 ; i < s1.len ; i++)
        temp.str[i] = s1.str[i];

    for ( int j = i , k = 0 ; j < temp.len ; j++,k++)
        temp.str[j] = s2.str[k];

    return temp;
}

String& String::operator+= (char s)
{
    char* temp = str;
    len++;
    str = new char [len];
    for ( int i = 0 ; i < len-1 ; i++)
        str[i] = temp[i];
    str[len-1] = s;

    return *this;
}

String& String::operator+= (String s)
{
    int tempLength = len;
    char* tempStr = str;
    len += s.len;
    str = new char [len];

    for ( int i = 0 ; i < tempLength ; i++ )
        str[i] = tempStr[i];

    for (int k = tempLength, j = 0; k < len ;k++,j++ )
        str[k] = s.str[j];

    return *this;
}

int String::compareStrings(const String& s1, const String& s2)
{
    if ( s1 == s2 )
        return 0;
    else
    {
        for (int i = 0 ; i < s1.length() ; i++ )
            if ( s1[i] > s2[i] )
                return 1;
    }

    return -1;
}

String String::reversedString (const String& s)
{
    String temp (new char [s.length()]);

    for ( int i = 0, k = temp.length() - 1 ; i < temp.length() ; i++, k--)
        temp.str[i] = s.str[k];

    return temp;
}

ostream& operator<< ( ostream& outs , const String s)
{
    for ( int i = 0 ; i < s.len ; i++)
        cout << s.str[i];
    return outs;
}

String::~String()
{
    delete [] str;
}

int main()
{
    String s1, s2;
    cout << "s1 is empty? " << s1.empty() << endl;
    cout << "s2 is empty? " << s2.empty() << endl;
    String s3 = "Hello";
    s1 = s2 = s3;
    cout << s1 << '\t' << s2 << '\t' << s3 << endl;
    if (s1 == s2)
        cout << "s1 and s2 are equal\n";
    else
        cout << "s1 and s2 are not equal\n";

    s1 = s1;
    cout << "\nIs there any problem here? " << s1 << endl << endl;

    s2 = "hi";
    s3 = s2;
    cout << s1 << '\t' << s2 << '\t' << s3 << endl;
    cout << "Now s1 is empty? " << s1.empty() << endl;
    cout << s1.length() << '\t' << s2.length() << '\t' << s3.length() << endl;

    cout << "--------------- 0 ---------------" << endl << endl;

    if (s1 == s2)
        cout << "They are equal\n";
    else
        cout << "They are not equal\n";

    if (s2 == "Hello")
        cout << "They are equal\n";
    else
        cout << "They are not equal\n";

    s1[0] = 'H';
    s1[1] = s1[4];
    for(int i = 0; i < s3.length(); ++i)
        cout << s3[i] << " ";
    cout << endl;
    cout << "s1 is " << s1 << endl;
    cout << "s2 is " << s2 << endl;

    cout << "--------------- 1 ---------------" << endl << endl;

    String s4;
    String space (" ");

    s4 = s1 + space + s2;
    cout << s4 << endl;

    cout << "s4 length is " << s4.length() << endl;
    if (s4 == s4)
        cout << "s4 equals s4\n";
    else
        cout << "s4 not equals s4\n";
    cout << endl;

    s3 = "Monday";
    cout << "s3 is " << s3 << endl;
    s3 = "";
    cout << "s3 is " << s3 << endl;
    String friday = "Friday";
    s3 = s3 + friday;
    cout << "s3 is " << s3 << endl;
    s3 = "SundaySunday";
    s3 = s3 + "   hahaha";
    cout << "s3 is " << s3 << endl;

    cout << "--------------- 2 ---------------" << endl << endl;

    String s5;
    cout << "Do we have output here? " << endl << endl;
    for(int i = 0; i < s5.length(); ++i)
        cout << s5[i] << '?';

    cout << "s4 is " << s4 << endl;
    cout << s4.upper() << endl;
    cout << s4 << endl;

    cout << "The index of l in " << s4 << " is " << s4.position('l') << endl;
    cout << "The index of k in " << s4 << " is " << s4.position('k') << endl;

    cout << "--------------- 3 ---------------" << endl << endl;

    cout << "s1 is: " << s1 << endl;
    char char_o = 'o';
    s1 += char_o;
    String str_o = "o";
    s1 += str_o;
    cout << "s1 now is: " << s1 << endl;
    String str;
    cout << "str is " << str << endl;
    char ch = 'A';
    for(int i = 0; i < 10; ++i)
    {
        str += ch;
        ch++;
    }
    String more = "...MORE";
    str += more;
    cout << "Now str is " << str << endl;

    cout << "--------------- 4 ---------------" << endl << endl;

    cout << "str length: " << str.length() << endl;
    cout << "substring starting at 2 with size 5 is " << str.substr(2,5) << endl;
    cout << "substring starting at 2 with size 20 is " << str.substr(2,20) << endl;
    cout << "substring starting at 7 with size 1 is " << str.substr(7,1) << endl;
    cout << "substring starting at 20 with size 5 is " << str.substr(20,5) << "empty string!" << endl;

    cout << "--------------- 5 ---------------" << endl << endl;

    s3 = "Hi";
    int index = s1.substring(s3);
    if (index >= 0)
        cout << "1) " << s3 << " is a substring of " << s1 << ", starting from index " << index << endl;
    else
        cout << "1) " << s3 << " is not a substring of " << s1 << endl;

    index = s1.substring("lo");
    if (index >= 0)
        cout << "2) " << "lo is a substring of " << s1 << ", starting from index " << index << endl;
    else
        cout << "2) " << "lo is not a substring of " << s1 << endl << endl;

    String s6;
    index = s1.substring(s6);
    if (index >= 0)
        cout << "3) " << s6 << " is a substring of " << s1 << ", starting from index " << index << endl;
    else
        cout << "3) " << s6 << " is not a substring of " << s1 << endl;


    String s = "aabcccdefefg";
    index = s.substring("bdg");
    if (index >= 0)
        cout << "4) bdg is a substring of " << s << ", starting from index " << index << endl;
    else
        cout << "4) bdg is not a substring of " << s << endl;

    index = s.substring("cde");
    if (index >= 0)
        cout << "5) cde is a substring of " << s << ", starting from index " << index << endl;
    else
        cout << "5) cde is not a substring of " << s << endl;

    s = "aabc";
    s1 = "aabc ";
    index = s.substring(s1);
    if (index >= 0)
        cout << "6) " << s1 << " is a substring of " << s << ", starting from index " << index << endl;
    else
        cout << "6) " << s1 << " is not a substring of " << s << endl;

    index = s.substring(s);
    if (index >= 0)
        cout << "7) " << s << " is a substring of " << s << ", starting from index " << index << endl;
    else
        cout << "7) " << s << " is not a substring of " << s << endl;


    cout << "--------------- 6 ---------------" << endl << endl;
    s1 = "hello";
    s2 = "hi";
    s3 = "he";
    s4 = "hello";
    s5 = "";
    cout << compareStrings (s1, s2) << endl; // the behavior of this function is the same as strcmp
    cout << compareStrings (s1, s3) << endl;
    cout << compareStrings (s1, s4) << endl;
    cout << compareStrings (s5, s2) << endl;
    cout << compareStrings (s2, s5) << endl;
    cout << compareStrings (s1, s1) << endl << endl;

    cout << s1 << endl;
    String reversed = reversedString (s1);
    cout << "The reversed string is " << reversed << endl;
    cout << "The original string is " << s1 << endl;

    if (reversedString (s1) == reversedString (s4))
        cout << "Yes, equal!" << endl;
    else
        cout << "No, not equal!" << endl;

    system("pause");
    return 0;
}

