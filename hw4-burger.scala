/*
    Course: CS451
    Student Name: Nick Burger
    Instructor: Dr. Cho
    Date of submission: 4/11/2023
    Program Description: HW4 -> functions in scala to do the following tasks:
                                - check if a given input is an element in a given list
                                - check if two list are equal
                                - append a list onto another list
                                - calculate quadratic roots
                                - calculate the factorial of a given input
                                - calculate the factorial nd avoid stack overflow
                                - find the third element in a given list
                                - find the nth element in a given list
 */


import scala.annotation.tailrec

@main def m() = {
  // checking for member
  // [[HW1: (10 pts) complete the member function
  def member(a: Int, b: List[Int]): Boolean = {
    var i = 0
    var found = false
    if(b == Nil){ //check if list is null
      found //return false
    }else { //if not null
      while (i < b.length && !found) { //loop through list and try to find member
        if (b(i) == a) { //if element in list matches
          found = true //found
        }
        i += 1
      }
    }
    found //return found value
  }

  val l1 = List(1, 2, 3, 4)
  println("#1")
  println(member(2, l1))
  println(member(5, l1))
  println
  // HW1]]

  // [[HW2: (10 pts) complete the list equality function
  // Assume that list of chars are passed as parameters
  val l2 = List('A', 'B', 'C', 'D')
  val l3 = List('A', 'C', 'D')
  val l4 = List('A', 'C', 'D')

  def equalsimp(a: List[Char], b: List[Char]): Boolean = {
    if (a.length != b.length) { //check if lengths of lists are the same
      false //if not false
    } else { //if lengths are the same
      var i = 0
      var equal = true //default to true
      while (i < a.length && equal) { //loop through lists and check if the elements are the same
        if (a(i) != b(i)) { //if not false
          equal = false
        }
        i += 1
      }
      equal //return equal value
    }
  }

  println("#2")
  println(equalsimp(l2, l3))
  println(equalsimp(l4, l3))
  println(equalsimp(l4, List('D', 'A', 'C')))
  println(equalsimp(l2, List('D', 'A', 'C', 'B')))
  println

  //extra credit attempt
  def equalsimpEC(a: List[Char], b: List[Char]): Boolean = {
    var equal = true
    if (a.length != b.length) {
      false
    } else {
        for(i <- a){ //loop through a list
          if(!b.contains(i)){ //if each element in a is not in b return false
            equal = false
          }
        }
      for(i <- b) { //loop through b list
        if(!a.contains(i)){ //if each element in b is not in a return false
          equal = false
        }
      }
      equal //return equal value
    }
  }

  println("Extra Credit:")
  println(equalsimpEC(l2, l3))
  println(equalsimpEC(l4, l3))
  println(equalsimpEC(l4, List('D', 'A', 'C')))
  println(equalsimpEC(l2, List('D', 'A', 'C', 'B')))
  println

  // HW2]]

  // [[HW3: (10 pts) Complete the append function
  def append[A](l1: List[A], l2: List[A]): List[A] = {
    var result = l1
    var i = 0
    while (i < l2.length) { //loop through list
      result = result :+ l2(i) //append values to result
      i += 1
    }
    result
  }

  println("#3")
  println(append(l2, l3))
  println(append(l4, l2))

  val l5 = List(1, 2, 3, 4)
  val l6 = List(10, 11)
  println(append(l5, l6))
  println
  // HW3]]

  // [[HW4: (10 pts) Complete the quadratic_roots function
  // hint: for square root, you can call math.sqrt() function
  def quadratic_roots(a: Int, b: Int, c: Int) = {
    val root_part = math.sqrt(b * b - 4 * a * c) / (2 * a)
    val minus_b = -b / (2 * a)

    List(minus_b + root_part, minus_b - root_part)
  }

  println("#4")
  println(quadratic_roots(1, -2, -3))
  println
  // HW4]]

  // [[HW5: (10 pts) Complete the factorial functin using recursion
  def factorial(n: Int): BigInt = {
    if (n < 0) throw new IllegalArgumentException("Number must be non-negative") //check if negative number
    else if (n == 0) 1 // if n = 0  return 1
    else {
      try { //try catch to handle stack overflow
        n * factorial(n - 1) //recursivly call function to find factorial
      } catch { //catch stack overflow and return 0
        case e: StackOverflowError => return BigInt(0)
      }
    }
  }

  println("#5")
  println(factorial(10))
  println(factorial(10000)) // Stack Overflow
  println
  // HW5]]

  // [[HW6: (10 pts) Complete the factorial function with tail recursion
  @tailrec
  def factHelper(n: Int, factPartial: BigInt): BigInt = {
    if (n == 0) factPartial
    else factHelper(n - 1, n * factPartial) //calculate factorial if != 0
  }

  def tailFactorial(n: Int): BigInt = {
    factHelper(n, 1) //send input
  }

  println("#6")
  println(tailFactorial(10000)) // much faster and no stack overflow
  println
  // HW6]]


  // Function composition
  def h[A, B, C](f: B => C, g: A => B): A => C =
    x => f(g(x))

  val add2 = (x: Int) => x + 2
  val times3 = (x: Int) => x * 3
  println("#7")
  println(h(add2, times3)(4))
  println

  // [[HW8: (10 pts) Complete the third_list function
  def third_list[A](ls: List[A]): A = {
    if (ls.length < 3) throw new IllegalArgumentException("List must have at least three elements")
    else ls(2) //return 2nd index
  }

  val l7 = List(1, 2, 3, 4)
  println("#8")
  println(third_list(l7))
  println(third_list(List(1, 2, (3, 4, 5), 6, 7)))
  println
  // HW8]]

  // [[HW9: (20 pts) Complete the nth_list function
  // this function returns the nth element in the list
  def nth_list[A](n: Int, ls: List[A]): A = {
    if (n < 0) throw new IllegalArgumentException("n must be non-negative")
    else ls(n - 1) //return nth index
  }

  println("#9")
  println(nth_list(2, l7))
  println(nth_list(2, List(1, 2, (3, 4, 5), 6, 7)))
  // HW9]]
}