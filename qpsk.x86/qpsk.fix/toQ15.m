function num = toQ15(X)
 num = [];
 for k = 1: size(X,2)
  n = toQ15_interface( X(k) );
  num = [num n]; 
 end 
