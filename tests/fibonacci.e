function fib(n::Integer)
  if n < 2
    n
  else
    fib(n-1) + fib(n-2)
  end
end

show(fib(10))
