#!/usr/bin/python
# coding: utf-8

from __future__ import division
from random import uniform

def direct_pi_estimation(N,k):
  # computes pi with direct sampling monte carlo alg
  # N : number of iterations
  # k : number of trials
  sum = 0
  for i in range(0,N):
    sum = sum + direct_pi(k)
  average_pi = sum / N
  return average_pi

def direct_pi(k):
  # computes pi with direct sampling
  # k : number of trials
  hits = 0 
  for i in range(0,k):
    x = uniform(-1,1)
    y = uniform(-1,1)
    if x*x + y*y <= 1 :
      hits = hits + 1
  estimated_pi = 4 * hits / k
  return estimated_pi
