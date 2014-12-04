
'''Self Define DFA Dead Exception'''
class DFADeadException(Exception):
    def __init__(self,cnt,q,input):
        Exception.__init__(self)
        self.cnt = cnt
        self.q = q
        self.input = input


'''A DFA takes five arguments: StateSet Alphabet TransformFunc InitialState FinalState'''
class DFA(object):
    def __init__(self,Q,S,T,q0,F):
        self.Q = Q          #Init State Q: A Set of possible state
        self.S = S          #Init Alphabet Sigma S: A Set of Character
        self.T = T          #Init TransFunction T: A callable object
        self.q0 = q0        #Init InitState q0: q0 in Q should be true
        self.F = F          #Init Final States: F should be contained in Q
        self.q = q0         #Init DFA Current State q with q0.


        if not q0 in Q:
            raise ValueError("Init State q0 is not in Available State Set Q")

        if not F.issubset(Q):
            raise ValueError("Final State Set F is not a subset of State Set Q")


    '''Judge Whether a string belongs to this DFA's Language'''
    def __call__(self,stringInput):
        self.q = self.q0        #Reset before start
        for cnt,e in enumerate(stringInput):
            oldState = self.q
            newState = self.T[oldState][e]
            infoString = "%d:\t[%s] -- (%s) --> [%s]" % (cnt,oldState,e,newState)
            print infoString
            if not newState:
                raise DFADeadException(cnt,oldState,cnt)
            self.q = newState
        return True if self.q in self.F else False

    
    '''Cartesian Product of two DFA'''
    def mul(self,other):
        newQ =  {(i,j) for i in self.Q for j in other.Q}    #Cartesian Product of State Set
        newS = self.S.union(other.S)            #Union of factors
        newd = { {} for i in newQ for j in newQ}
                
        newq0 = (self.q0,other.q0);
        newF = {(i,j) for i in self.F for j in other.F}    #Cartesian Product of Final State Set



if __name__ == "__main__":


    state = {'A','B','C','D'}
    sigma = {0,1,2}
    transf = {
      'A':{0:'C',1:'A',2:'D'},
      'B':{0:'A',1:'B',2:None},
      'C':{0:'B',1:'B',2:None},
      'D':{0:'D',1:'D',2:None}
        }
    q0 = 'B'
    F = {'D'}

    dfa = DFA(state,sigma,transf,q0,F)
    try:
        dfa([0,1,0,2])
    except DFADeadException,e:
        print "DFA is Dead at Step:%d State:[%s],Input[%s]" % (e.cnt,e.q,e.input)
        
    