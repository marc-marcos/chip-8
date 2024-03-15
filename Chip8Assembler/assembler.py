import sys

def Usage(executable_name):
    print(f"Usage: python3 {executable_name} intput_file output_file")
    sys.exit(1)

def separar_operandos(instruccion):
    return instruccion.split(" ")

def traducir_instruccion(instruccion_separada):
    if ("CLS" in instruccion_separada[0]):
        return "00e0"
    
    elif ("RET" in instruccion_separada[0]):
        return "00ee"

    elif ("SYS" in instruccion_separada[0]):
        return f"0{instruccion_separada[1][0]}{instruccion_separada[1][1]}{instruccion_separada[1][2]}" 

    elif ("JP" in instruccion_separada[0]): # Falta otro modo de direccionamiento
        return f"1{instruccion_separada[1][0]}{instruccion_separada[1][1]}{instruccion_separada[1][2]}"

    elif ("CALL" in instruccion_separada[0]):
        return f"2{instruccion_separada[1][0]}{instruccion_separada[1][1]}{instruccion_separada[1][2]}"

    elif ("SE" in instruccion_separada[0]):
        if (instruccion_separada[-1][-3] == 'V'):
            return f"5{instruccion_separada[1][-2]}{instruccion_separada[2][-2]}0"

        else:
            return f"3{instruccion_separada[1][-2]}{instruccion_separada[-1][-3]}{instruccion_separada[-1][-2]}"

    elif ("SNE" in instruccion_separada[0]):
        if (instruccion_separada[-1][-3] == 'V'):
            return f"4{instruccion_separada[1][1]}{instruccion_separada[-2][-2]}{instruccion_separada[-1][-2]}"
        
        else:
            return f"9{instruccion_separada[1][-2]}{instruccion_separada[-1][-2]}0"
    
    elif ("ADD" in instruccion_separada[0]): # Falta el caso en que los dos operandos sean registros y el del I
        return f"7{instruccion_separada[1][-2]}{instruccion_separada[-1][-3]}{instruccion_separada[-1][-2]}"

    elif ("OR" in instruccion_separada[0]):
        return f"8{instruccion_separada[-2][-2]}{instruccion_separada[-1][-2]}1"

    elif ("AND" in instruccion_separada[0]):
        return f"8{instruccion_separada[-2][-2]}{instruccion_separada[-1][-2]}2"

    elif ("XOR" in instruccion_separada[0]):
        return f"8{instruccion_separada[-2][-2]}{instruccion_separada[-1][-2]}3"

    elif ("SUB" in instruccion_separada[0]):
        return f"8{instruccion_separada[-2][-2]}{instruccion_separada[-1][-2]}5"

    elif ("SUBN" in instruccion_separada[0]):
        return f"8{instruccion_separada[-2][-2]}{instruccion_separada[-1][-2]}7"

    elif ("SHL" in instruccion_separada[0]):
        return f"8{instruccion_separada[-2][-2]}{instruccion_separada[-1][-2]}e"

    elif ("SHR" in instruccion_separada[0]):
        return f"8{instruccion_separada[-2][-2]}{instruccion_separada[-1][-2]}6"

    elif ("RND" in instruccion_separada[0]):
        return f"c{instruccion_separada[1][-2]}{instruccion_separada[-1][-3]}{instruccion_separada[-1][-2]}"

    elif ("DRW" in instruccion_separada[0]):
        return f"d{instruccion_separada[1][-2]}{instruccion_separada[2][-2]}{instruccion_separada[-1][-2]}"

    elif ("SKP" in instruccion_separada[0]):
        return f"e{instruccion_separada[-1][-2]}9e"

    elif ("SKNP" in instruccion_separada[0]):
        return f"e{instruccion_separada[-1][-2]}a1"

    elif ("LD" in instruccion_separada[0]):
        if ("V" in instruccion_separada[1]):
            if ("V" in instruccion_separada[2]): # LD Vx, Vy
                return f"8{instruccion_separada[1][-2]}{instruccion_separada[2][-2]}0"

            elif ("DT" in instruccion_separada[2]): # LD Vx, DT
                return f"f{instruccion_separada[1][-2]}07"

            elif ("K" in instruccion_separada[2]): # LD Vx, K
                return f"f0{instruccion_separada[1][-2]}a"
            
            elif ("[I]" in instruccion_separada[2]): # LD Vx, [I]
                return f"f{instruccion_separada[1][-3]}55"
            
            else: # LD Vx, by
                return f"6{instruccion_separada[1][-2]}{instruccion_separada[-1][-3]}{instruccion_separada[-1][-2]}"
        
        else: # Not a register in the first operand
            if ("I" in instruccion_separada[1]): # LD I, addr
                return f"a{instruccion_separada[-1][:-1]}"

            elif ("DT" in instruccion_separada[1]): # LD DT, Vx
                return f"f{instruccion_separada[-1][-2]}15"

            elif ("ST" in instruccion_separada[1]): # LD ST, Vx
                return f"f{instruccion_separada[-1][-2]}18"

            elif ("F" in instruccion_separada[1]): # LD F, Vx
                return f"f{instruccion_separada[-1][-2]}29"

            elif ("B" in instruccion_separada[1]): # LD B, Vx
                return f"f{instruccion_separada[-1][-2]}33"

            elif ("[I]" in instruccion_separada[1]): # LD [I], Vx
                return f"f{instruccion_separada[-1][-2]}55"

    # Default case

    else:
        return "instruccion_no_reconocida"
    
if __name__=='__main__':
    if (len(sys.argv) != 3): Usage(sys.argv[0])

    output = ""

    with open(sys.argv[1], 'r') as file:
        lines = file.readlines()

        for line in lines:
            print(separar_operandos(line))
            print(traducir_instruccion(separar_operandos(line)))
            output += traducir_instruccion(separar_operandos(line))

    with open(sys.argv[2], 'w') as file:
        file.write(output.lower())
    
    print(output)
        
