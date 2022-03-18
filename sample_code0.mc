#full credit for running (when your compiler is complete) this type of code (no bonus)
#program to calculate fibonacci series and display on stdout
func int main:
begin # Three address code generation starts after here
	#variable declarations, note num and i are not initialized
	x<-0 int;
	y<-1 int;
	z<-0 int;
	i    int;
	num  int;
	print "Enter the number :";#print 
    in num; #take input
	if num < 0:
	begin
		print "negative number entered\n";#print
		return 0;# this statement just halt the program
	end
    print "\nThe fibonacci series :";#print
    for i<-0, i<num, i<-i+1: # loop calculating actual output
    begin
        print x;
        print " ";
        z <- x + y; # store sum in z
        x <- y; #assign value of y to x
        y <- z; #assign values of z to y
    end
    print "\n";
    return 0;#halts program
	
end