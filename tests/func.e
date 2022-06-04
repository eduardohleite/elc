function sqr(x::Integer)
  x*x
end

function sum(x1::Integer, x2::Integer)
  x1 + x2
end

show(sum(1, sqr(2)))