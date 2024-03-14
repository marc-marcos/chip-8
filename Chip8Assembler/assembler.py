import sys

def Usage(executable_name):
    print(f"Usage: python3 {executable_name} file_name")
    sys.exit(1)

def separar_operandos(instruccion):
    return instruccion.split(" ")

def traducir_instruccion(instruccion_separada):
    if ("CLS" in instruccion_separada[0]):
        return "00e0"
    
    if ("RET" in instruccion_separada[0]):
        return "00ee"

    if ("SYS" in instruccion_separada[0]):
        return f"0{instruccion_separada[1][0]}{instruccion_separada[1][1]}{instruccion_separada[1][2]}" 

    
if __name__=='__main__':
    if (len(sys.argv) != 2): Usage(sys.argv[0])

    output = ""

    with open(sys.argv[1], 'r') as file:
        lines = file.readlines()

        for line in lines:
            print(separar_operandos(line))
            print(traducir_instruccion(separar_operandos(line)))
        
