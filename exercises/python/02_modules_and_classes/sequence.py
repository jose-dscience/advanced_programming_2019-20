#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import copy

class Sequence():
    def __init__(self, input):
        self.seq = list(input)
    
    def __str__(self):
        return "<seq: {0}>".format(self.seq)
    
    def __len__(self):
        return len(self.seq)
    
    def __eq__(self, other):
        return self.seq == other.seq
    
    def __getitem__(self, i):
        return self.seq[i]
    
    def __setitem__(self, i, n):
        self.seq[i] = n
        
    def __delitem__(self, item):
        del self.seq[item]
    
    def __iter__(self):
        return iter(self.seq)
    
    def insert(self, pos, val):
        if(pos >= len(self)):
            for i in range(len(self),pos+1,1):
                self.seq.append(0)
            self.seq[pos] = val
        else:
            self.seq.append(0)
            for i in range(len(self)-1,pos,-1):
                self[i] = self[i-1] 
            self[i] = val
    
    def append(self, val):
        self.seq.append(val)
    
    def __copy__(self):
        newseq = Sequence([])
        for x in self:
            newseq.append(x)
        return newseq