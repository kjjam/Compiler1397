from collections import deque
from collections import OrderedDict
from pprint import pprint
import firstfollow
from firstfollow import production_list, nt_list as ntl, t_list as tl
import string_validating
import sys

nt_list, t_list=[], []
final=[]
class State:

	_id=0
	def __init__(self, closure):
		self.closure=closure
		self.no=State._id
		State._id+=1

def closure(items):

	global production_list

	while True:
		flag=0
		for i in items:	
	
			if i.index('.')==len(i)-1: continue
			
			Y=i.split('->')[1].split('.')[1][0]

			for prod in production_list:
				head, body=prod.split('->')
				
				if head!=Y: continue

				newitem=Y+'->.'+body
				
				if newitem not in items:
					items.append(newitem)
					flag=1
		if flag==0: break

	return items

def goto(items, symbol):

	global production_list
	initial=[]

	for i in items:
		if i.index('.')==len(i)-1: continue

		head, body=i.split('->')
		seen, unseen=body.split('.')


		if unseen[0]==symbol and len(unseen) >= 1:
			initial.append(head+'->'+seen+unseen[0]+'.'+unseen[1:])

	return closure(initial)



def calc_states():

	def contains(states, t):

		for s in states:
			if sorted(s)==sorted(t): return True

		return False

	global production_list, nt_list, t_list

	head, body=production_list[0].split('->')
	states=[closure([head+'->.'+body])]
	
	while True:
		flag=0
		for s in states:
			for e in nt_list+t_list:
				t=goto(s, e)
				if t == [] or contains(states, t): continue

				states.append(t)
				flag=1

		if not flag: break
	
	return states 


def make_table(states):
	global final
	global nt_list, t_list

	def getstateno(closure):

		for s in states:
			if sorted(s.closure)==sorted(closure): return s.no

	def getprodno(closure):

		closure=''.join(closure).replace('.', '')
		return production_list.index(closure)

	SLR_Table=OrderedDict()
	
	for i in range(len(states)):
		states[i]=State(states[i])

	for s in states:
		SLR_Table[s.no]=OrderedDict()

		for item in s.closure:
			head, body=item.split('->')
			if body=='.': 
				for term in t_list:
					if term not in SLR_Table[s.no].keys():
						SLR_Table[s.no][term]={'r'+str(getprodno(item))}
					else: SLR_Table[s.no][term] |= {'r'+str(getprodno(item))}
				continue

			nextsym=body.split('.')[1]
			if nextsym=='':
				if getprodno(item)==0:
					SLR_Table[s.no]['$']='accept'
				else:
					for term in ntl[head].follow: #for term in t_list: 
						if term not in SLR_Table[s.no].keys():
							SLR_Table[s.no][term]={'r'+str(getprodno(item))}
						else: SLR_Table[s.no][term] |= {'r'+str(getprodno(item))}
				continue

			nextsym=nextsym[0]
			t=goto(s.closure, nextsym)
			if t != []: 
				if nextsym in t_list:
					if nextsym not in SLR_Table[s.no].keys():
						SLR_Table[s.no][nextsym]={'s'+str(getstateno(t))}
					else: SLR_Table[s.no][nextsym] |= {'s'+str(getstateno(t))}

				else: SLR_Table[s.no][nextsym] = str(getstateno(t))
	for st in SLR_Table:
		final.append(dict(SLR_Table[st]))
	return SLR_Table

def augment_grammar():

	for i in range(ord('Z'), ord('A')-1, -1):
		if chr(i) not in nt_list:
			start_prod=production_list[0]
			production_list.insert(0, chr(i)+'->'+start_prod.split('->')[0]) 
			return

def main():

	global production_list, ntl, nt_list, tl, t_list	

	firstfollow.main()

	for nt in ntl:
		firstfollow.compute_first(nt)
		firstfollow.compute_follow(nt)
		
	

	augment_grammar()
	nt_list=list(ntl.keys())
	t_list=list(tl.keys()) + ['$']

	table=make_table(calc_states())

	print("\n========= TABLE ========== \n")

	sys.stdout.write("\t{}\t{}\n".format('\t'.join(t_list), '\t'.join(nt_list)))

	for i, j in table.items():
			sys.stdout.write("\n{}\t".format(i))
			for sym in t_list+nt_list:
				if sym in table[i].keys():
					if type(table[i][sym])!=type(set()): 
						sys.stdout.write("{}\t".format(table[i][sym]))
					else:
						sys.stdout.write("{}\t".format(', '.join(table[i][sym])))
				else:
					sys.stdout.write("\t")
			sys.stdout.write("\n")
			s, r=0, 0

			for p in j.values():
				if p!='accept' and len(p)>1:
					p=list(p)
					if('r' in p[0]): r+=1
					else: s+=1
					if('r' in p[1]): r+=1
					else: s+=1		
			if r>0 and s>0: sr+=1
			elif r>0: rr+=1

	return 

if __name__=="__main__":
	main()
	# print(final)
	inString=input("\n please enter your string to validate  :  ")
	string_validating.validation(firstfollow.production_list, final, inString+"$")




