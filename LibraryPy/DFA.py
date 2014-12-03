class DFADeadException(Exception):
    def __init__(self,cnt,q,input):
        Exception.__init__(self)
        self.cnt = cnt
        self.q = q
        self.input = input


'''A DFA takes five arguments: StateSet Alphabet TransformFunc InitialState FinalState'''
class DFA(object):
    def __init__(self,Q,Sigma,d,q0,F):
        self.Q = Q           #Init State Q: A Set of possible state
        self.Sigma = Sigma       #Init Alphabet Sigma: A Set of Character
        self.d = d           #Init TransFunction delta: A callable object
        self.q = q0          #Init InitState q0: q0 in Q should be true
        self.F = F           #Init Final States: F should be contained in Q

        if not q0 in Q:
            raise ValueError("Init State q0 is not in Available State Set Q")

        if not F.issubset(Q):
            raise ValueError("Final State Set F is not a subset of State Set Q")


    def __call__(self,string):
        for cnt,letter in enumerate(string):
            newState = self.d(self.q,letter)
            infoString = "%d:\t[%s] -- (%s) --> [%s]" % (cnt,self.q,letter,newState)
            print infoString
            if not newState:
                raise DFADeadException(cnt,self.q,letter)
            self.q = newState
        return True if self.q in self.F else False

    
    '''Cartesian Product of two DFA'''
    def mul(self,other):
        newQ =  {(i,j) for i in self.Q for j in other.Q}
        newSigma


if __name__ == "__main__":


    state = {'A','B','C','D'}
    sigma = {0,1,2}
    transf = lambda q,a:{
      'A':{0:'C',1:'A',2:'D'},
      'B':{0:'A',1:'B',2:None},
      'C':{0:'B',1:'B',2:None},
      'D':{0:'D',1:'D',2:None}
        }[q][a]
    q0 = 'B'
    F = {'D'}

    dfa = DFA(state,sigma,transf,q0,F)
    try:
        dfa([0,1,0,2])
    except DFADeadException,e:
        print "DFA is Dead at Step:%d State:[%s],Input[%s]" % (e.cnt,e.q,e.input)
        
    