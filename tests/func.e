function sqr(x::Integer)
  x*x
end

function sum(x1::Integer, x2::Integer)
  x1 + x2
end

sqr(2)
sqr(3)
sqr(5)


sum(1,1)
sum(2,2)

sum(1, sqr(2))