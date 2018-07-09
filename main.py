import subprocess
import os
print("Hello please select what you want")
print("1- lexical Analysis")
print("2- syntax Analysis")
first_step = input()
if(first_step == '1'):
    os.system('lexer.exe')
elif(first_step == '2'):
    print("type of syntax analysis")
    print ("1- LR(0)\n2- LR(1)\n3- LALR(1)\n4- SLR(1)")
    syntax_step = input()
    syntax_step = int(syntax_step)
    print("OK! Go and enter the grammer. like\nS->(A)\nA->a\nA->\n\n====   Enter   =====")
    if syntax_step == 1:
        res = os.system('python3 lr0_backend_only.py')
    elif syntax_step == 2:
        res = os.system('python3 clr_backend_only.py')
    elif syntax_step == 3:
        res = os.system('python3 lalr1_backend_only.py')
    elif syntax_step == 4:
        res = os.system('python3 slr_backend_only.py')
