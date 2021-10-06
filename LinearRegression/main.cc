#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        cout << "Please give the path to the input csv file" << endl;
        return 1;
    }
    string cursor;
    ifstream fileStream(argv[1]);
    if (!fileStream)
    {
        cerr << "Error: file could not be opened at " << argv[1] << endl;
        exit(1);
    }
    int lines = 0;
    int fields = 0;
    string *fieldNames;
    while (getline(fileStream, cursor))
    {
        if (lines == 0)
        {
            // Checking how much fields there are in the csv file
            for (int i = 0; i < cursor.length(); i++)
            {
                if (cursor[i] == ',')
                {
                    fields++;
                }
            }
            // Validating numbers of field
            if (fields > 0)
            {
                // there is one field more than the commas so incrementing a fields number
                // and adding one comma to the last of the cursor for taking the last field in the next part of code
                fields++;
                cursor += ',';
            }
            else
            {
                cerr << "Input file should at least have 2 fields!" << endl;
                return 1;
            }
            // Making an array of field names with the length of fields
            fieldNames = new string[fields];

            // Adding the field names to the field names array
            int nextFieldStartingIndex = 0;
            int fieldsAdded = 0;
            for (int i = 0; i < cursor.length(); i++)
            {
                if (cursor[i] == ',')
                {
                    fieldNames[fieldsAdded] = cursor.substr((nextFieldStartingIndex), (i - nextFieldStartingIndex));
                    fieldsAdded++;
                    nextFieldStartingIndex = (i + 1);
                }
            }
        }

        lines++;
    }

    fileStream.close();

    cout << "Fields are: " << endl;
    for (int i = 0; i < fields; i++)
    {
        cout << fieldNames[i] << endl;
    }

    delete[] fieldNames;

    return 0;
}
