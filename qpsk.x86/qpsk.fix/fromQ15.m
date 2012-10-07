function num = fromQ15(X)
 num = [];
 for k = 1: size(X,2)
   n = X(k) / 2^15;
   num = [num n];
 end
 
end 