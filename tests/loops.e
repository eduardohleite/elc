a = 0
b = 0

for i in 1:1000
  a = a + i
  for j in 1:1000
    b = b + j
  end
end

a
b