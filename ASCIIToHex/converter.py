import binascii
import sys

def Usage(executable_name):
    print(f"Usage: python3 {executable_name} file_name")
    sys.exit()

if __name__=='__main__':
    if (len(sys.argv) != 2): Usage(sys.argv[0])

    with open(sys.argv[1], 'r') as file:
        data = file.read()

    with open("output.hex", 'wb') as file:
        file.write(binascii.unhexlify(data))