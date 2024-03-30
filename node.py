Left = 1 
Right = 0

nodeKey = lambda x: x.p 

def Nodelize(dic:dict):
    arr = []
    for key in dic.keys():
        newNode = Node(key)
        newNode.p = dic[key]
        arr.append(newNode)
    return arr

class Node:
    def __init__(self, value=None) -> None:
        self.value = value
        self.p = 0
        self.big = None
        self.small = None

    def __add__(self, other):
        newNode = Node()
        newNode.big = self #self is bigger in most cases
        newNode.small = other
        newNode.p = other.p  + self.p
        return newNode
    
    def __repr__(self) -> str:
        return str([self.value,self.p, self.big, self.small])

class NodeList(list):
    def __init__(self, freq:dict):
        super().__init__(Nodelize(freq))
        self.freq = freq
    
    def step(self):
        self[-2] += self[-1]
        self.pop(-1)
        self.sort(key=nodeKey, reverse=True)
    
    def makeTree(self):
        while self.__len__() > 1:
            self.step()
    
    def trace(self, buffer:dict=None, root:Node = None, currentBin=""):
        if buffer == None:
            buffer = self.freq.copy()
        
        if root == None:
            root = self[0]
        
        if root.value:
            buffer[root.value] = currentBin
        
        if root.big:
            self.trace(buffer, root.big, currentBin+"1")
        
        if root.small:
            self.trace(buffer, root.small, currentBin+"0")        

        return buffer


