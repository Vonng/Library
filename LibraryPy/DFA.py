
'''Self Define DFA Dead Exception'''
class DFADeadException(Exception):
    def __init__(self,cnt,q,input):
        Exception.__init__(self)
        self.cnt = cnt
        self.q = q
        self.input = input


'''A DFA takes five arguments: StateSet Alphabet TransformFunc InitialState FinalState'''
class DFA(object):
    def __init__(self,states,alphabet,transfer,initState,finalState,name="Default"):
        self.Q = set(states.keys())          #Init State Q: A Set of possible state
        self.S = set(alphabet.keys())         #Init Alphabet Sigma S: A Set of Character
        self.T = {}
        for state in self.Q:
            self.T[state] = {}
            for char in self.S:
                exist = bool(transfer.get(state) and transfer.get(state).get(char))
                self.T[state][char] = transfer[state][char]  if exist else None

        self.q0 = initState        #Init InitState q0: q0 in Q should be true
        self.F = finalState          #Init Final States: F should be contained in Q
        self.q = initState         #Init DFA Current State q with q0.
        self.name = name

        if not self.q0 in self.Q:
            raise ValueError("DFA:%s\tInit State q0 is not in Available State Set Q" % self.name)

        if not self.F.issubset(self.Q):
            raise ValueError("DFA:%s\tFinal State Set F is not a subset of State Set Q")


    '''It returns new state. And return None if it shows explicitly in DFA's Transfer Table'''
    def runStep(self,state,char):
        if not self.T.get(state):
            raise KeyError("DFA:%s\t No Such State in DFA")
        if not char in self.S:
            return state    #If this charactor is not in Alphabet, It means no change to the DFA
        return self.T[state][char]


    '''It returns the final state DFA reaches. None if DFA is dead'''
    def runString(self,state,string):
        tempState = state
        for e in string:
            tempState = self.runStep(tempState,e)
            if not tempState:
                return None #Prevent Situation: None ---> ?
        return tempState


    '''Judge Whether a string belongs to this DFA's Language'''
    def __call__(self,stringInput):
        self.q = self.q0        #Reset before start
        for cnt,e in enumerate(stringInput):
            oldState = self.q
            newState = self.T[oldState][e]
            infoString = "%d:\t[%s] -- (%s) --> [%s]" % (cnt,oldState,e,newState)
            print infoString
            if not newState:
                return None
                #raise DFADeadException(cnt,oldState,cnt)
            self.q = newState
        result,self.q = self.q,self.q0 #restore status
        return result
    
    '''Cartesian Product of two DFA'''
    def __mul__(lhs,rhs):
        newQ = {(i,j) for i in lhs.Q for j in rhs.Q}    #Cartesian Product of State Set
        newS = lhs.S.union(rhs.S)            #Union of factors
        newT = {begin:{ letter:None for letter in newS } for begin in newQ}
        for begin in newQ:
            for letter in newS:
                p,q = begin #Unpack to two state
                newp = lhs.runStep(p,letter)
                newq = rhs.runStep(q,letter)
                if newp and newq:
                    newT[begin][letter] = (newp,newq)
                
        newq0 = (lhs.q0,rhs.q0)
        newF = {(i,j) for i in lhs.F for j in rhs.F}    #Cartesian Product of Final State Set
        return DFA(newQ,newS,newT,newq0,newF,"(%s,%s)" % (lhs.name,rhs.name))



if __name__ == "__main__":

    storeDFA = {
        'name' : "store",
        'states' : {
                    'a':"Begin",
                    'b':"Paid",
                    'c':"Paid|Delivered",
                    'd':"Paid|Redeemed",
                    'e':"Paid|Deliverd|Redeemed",
                    'f':"Paid|Redeemed|Transfered",
                    'g':"Paid|Redeemed|Transfered|Deliverd|Final"
                    },
        'alphabet':{'P':'pay',
                    'R':'redeem',
                    'T':'transfer',
                    'D':'deliver',
                    },
        'transfer':{
            'a':{'P':'b'},
            'b':{'R':'b','D':'c',},
            'c':{'R':'e'},
            'd':{'T':'f'},
            'e':{'T':'g'},
            'f':{'D':'g'},
            'g':{}
            },
        'initState':'a',
        'finalState':{'g'}
        }

    bankDFA = {
        'name' : "store",
        'states' : {
                    '1':"Begin",
                    '2':"Canceled",
                    '3':"Redeem",
                    '4':"Redeem|Transfered",
                    },
        'alphabet':{'R':'redeem',
                    'C':'Cancel',
                    'T':'transfer',
                    },
        'transfer':{
            '1':{'C':'2','R':'3'},
            '2':{},
            '3':{'T':'4'},
            '4':{},
            },
        'initState':'1',
        'finalState':{'2','4'}
        }

    store = DFA(**storeDFA)
    bank = DFA(**bankDFA)

    #store('PDRTP')
    bank('C')
    print "="*80
    bank('RT')    
    print "="*80
    store_bank = store * bank

    store_bank('P')