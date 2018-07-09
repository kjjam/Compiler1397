productions = ['Z->s', 's->fffD', 'D->rrrT', 'T->eee']
states =  [
{'s': '1', 'f': {'s2'}}, 
{'$': 'accept'}, 
{'f': {'s3'}},
 {'f': {'s4'}}, 
 {'D': '5', 'r': {'s6'}},
 {'$': {'r1'}}, 
 {'r': {'s7'}}, 
 {'r': {'s8'}}, 
 {'T': '9', 'e': {'s10'}}, 
 {'$': {'r2'}}, 
 {'e': {'s11'}}, 
 {'e': {'s12'}},
  {'$': {'r3'}}]
string = "fffrrreee$"



def validation(productions, states, string):
    string = list(string)
    stack = [0]
    pntr = 0
    def goto():
        # global stack
        stack.append(int(states[stack[-2]][stack[-1]]))
        return

    while len(string)!=0 or stack!=['Z']:
        try :
            # print(list(states[stack[-1]][string[0]]))
            # print(type(list(states[stack[-1]][string[0]])))
            if states[stack[-1]][string[0]] == 'accept': 
                print('validated')
                break
            transition = list(list(states[stack[-1]][string[0]])[0])            # [r,3]
            pntr+=1
        
            if transition[0] == 's':
                stack.append(string[0])
                del(string[0])
                stack.append(int("".join(transition[1:])))
            elif transition[0] == 'r':
                reduceProduct = productions[int(transition[1])].split("->")
                tempBody = reduceProduct[1]
                temp = stack
                ctr=1
                if tempBody == '':
                    stack.append(reduceProduct[0])
                    goto()
                    continue

                while tempBody:
                    symbol= temp.pop()
                    if type(symbol)==int and ctr%2 != 0:
                        # temp.pop()
                        ctr+=1
                    else:
                        tempBody=list(tempBody)
                        a = tempBody.pop()
                        if symbol == a:
                            ctr+=1
                            if tempBody==[]:
                                stack.append(reduceProduct[0])
                                goto()
                        else:
                            print("not valid")
                            break

        except:
            print('not valid ! ')
            break

# validation(productions, states, string)