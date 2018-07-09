from collections import deque
from collections import OrderedDict
from pprint import pprint
import firstfollow
from firstfollow import production_list, nt_list as ntl, t_list as tl
import string_validating
import sys

nt_list, t_list=[], []
final=[]


def deleteBackslash(strings):
	temp=[]
	for s in strings:
		if "\n" in s:
			temp.append(s[:-1])
		else :
			temp.append(s)
	return temp



class State:
	_id=0
	def __init__(self, closure):
		self.closure=closure
		self.no=State._id
		State._id+=1

class Item(str):
	def __new__(cls, item, lookahead=list()):
		self=str.__new__(cls, item)
		self.lookahead=lookahead
		return self

	def __str__(self):
		return super(Item, self).__str__()+", "+'|'.join(self.lookahead)
		

def closure(items):   #just make new produces sentences, items= closure

	def exists(newitem, items):
		for i in items:
			if i==newitem and sorted(set(i.lookahead))==sorted(set(newitem.lookahead)):
				return True
		return False


	global production_list

	while True:
		flag=0
		for i in items:	
			
			if i.index('.')==len(i)-1: continue

			Y=i.split('->')[1].split('.')[1][0]			# 

			if i.index('.')+1<len(i)-1:
				lastr=list(firstfollow.compute_first(i[i.index('.')+2])-set(chr(1013)))
				
			else:
				lastr=i.lookahead
			
			for prod in production_list:
				head, body=prod.split('->')
				
				if head!=Y: continue
				
				newitem=Item(Y+'->.'+body, lastr)

				if not exists(newitem, items):
					items.append(newitem)
					flag=1
		if flag==0: break

	return items

def goto(items, symbol):			# move ' . ' one further

	global production_list
	initial=[]

	for i in items:
		if i.index('.')==len(i)-1: continue

		head, body=i.split('->')
		seen, unseen=body.split('.')


		if unseen[0]==symbol and len(unseen) >= 1:
			initial.append(Item(head+'->'+seen+unseen[0]+'.'+unseen[1:], i.lookahead))

	return closure(initial)


def calc_states():	
	global final
	def contains(states, t):

		for s in states:
			if len(s) != len(t): continue

			if sorted(s)==sorted(t):
				for i in range(len(s)):
						if s[i].lookahead!=t[i].lookahead: break
				else: return True

		return False


	global production_list, nt_list, t_list

	head, body=production_list[0].split('->')


	states=[closure([Item(head+'->.'+body, ['$'])])]
	
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

	global nt_list, t_list

	def getstateno(t):

		for s in states:
			if len(s.closure) != len(t): continue

			if sorted(s.closure)==sorted(t):
				for i in range(len(s.closure)):
						if s.closure[i].lookahead!=t[i].lookahead: break
				else: return s.no

		return -1

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
				for term in item.lookahead: 
					if term not in SLR_Table[s.no].keys():
						SLR_Table[s.no][term]={'r'+str(getprodno(item))}
					else: SLR_Table[s.no][term] |= {'r'+str(getprodno(item))}
				continue

			nextsym=body.split('.')[1]
			if nextsym=='':
				if getprodno(item)==0:
					SLR_Table[s.no]['$']='accept'
				else:
					for term in item.lookahead: 
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

	#for i in range(ord('Z'), ord('A')-1, -1):
#		if chr(i) not in nt_list:
#			start_prod=production_list[0]
#			production_list.insert(0, chr(i)+'->'+start_prod.split('->')[0]) 
#			return
	production_list.insert(0, "S'"+'->'+production_list[0].split('->')[0]) 

def main():

	global production_list, ntl, nt_list, tl, t_list	
	

	# contentMain = [c[:-1] for c in content if c and ("\n" in c)]
	# print(content)
	firstfollow.main()

	augment_grammar()
	nt_list=list(ntl.keys())
	t_list=list(tl.keys()) + ['$']



	j=calc_states()

	ctr=0
	# for s in j:
	# 	print("Item{}:".format(ctr))
	# 	for i in s:
	# 		print("\t", i)
	# 	ctr+=1

	table=make_table(j)
	print(" ======== table ======== \n ")

	sr, rr=0, 0

	for i, j in table.items():
		# print(i, "\t", j)
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





	# sys.stdout.write('.')
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
	print("\n\n\n", sr, "s/r conflicts |", rr, "r/r conflicts\n")




	return 

if __name__=="__main__":
	main()
	inString=input("\n please enter your string to validate  :  ")
	string_validating.validation(firstfollow.production_list, final, inString+"$")

	




