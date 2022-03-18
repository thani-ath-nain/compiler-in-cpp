#if you were able to run this code (when your compiler is finished) you will get 2 bonus marks
#1) The for loop is inside else part
#2) The list initialization at line 8

#program to calculate fibonacci series and display on stdout
func int main:
begin # Three address code generation starts after here
	#variable declarations, note num and i are not initialized
	x<-0, y<-1, z<-0, i, num int;
	print "Enter the number :";#print 
	in num;# take input in num variable
	if num < 0:
	begin
		print "negative number entered\n";#print
		return 0;# this statement just halt the program
	end
	else:
	begin
		print "\nThe fibonacci series :";#print
		for i<-0, i<num ,i<-i+1: # loop calculating actual output
		begin
			print x;
			print " ";
			z <- x + y; # store sum in z
			x <- y; #assign value of y to x
			y <- z; #assign values of z to y
		end
	end
	return 0;#halts program
end