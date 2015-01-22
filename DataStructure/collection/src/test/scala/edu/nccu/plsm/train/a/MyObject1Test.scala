package edu.nccu.plsm.train.a

import java.util

import org.specs2.mutable.Specification

class MyObject1Test extends Specification {
  var iterable = new MyObject1[Int]
  override def is =
  s2"""$sequential
This is a specification to check the MyObject1 class

Testing MyObject1[Int]#size:
   |initialize:
   |  contain 0 element                          $eq0
   |add '0':
   |  return true                                $add0
   |    contains 1 element                       $eq1
   |add '1':  
   |  return true                                $add1
   |    contains 2 elements                      $eq2
   |add '0', '1', '2':
   |  return true                                $add123
   |    and contains 5 elements.                 $eq5
    """ ^
  end
  
  def eq(e : Int) = (iterable size) must be equalTo e
  def eq0 = eq(0)
  def eq1 = eq(1)
  def eq2 = eq(2)
  def eq5 = eq(5)
  
  def add(e : Int) = iterable add e must beTrue
  def add0 = add(0)
  def add1 = add(1)
  def add123 = {
    add(0)
    add(1)
    add(2)
  }
  
}
