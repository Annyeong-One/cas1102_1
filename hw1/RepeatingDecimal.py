import math
import re

########################################################
# doneTODO: MUST REPLACE THIS WITH YOUR STUDENT ID
student_id = "2025150015"  # Replace with your student ID
########################################################

class RepeatingDecimal:
    # doneTODO: IMPLEMENT THIS CONSTRUCTOR (Place for definition)
    def __init__(self, sign, int_part, non_repeat, repeat):
        """
        Initializes a RepeatingDecimal object.
        The number being represented is of the form: (sign) int_part.non_repeat[repeat part] (Note: the reason we use integers for int_part and non_repeat is to avoid floating point precision issues)
        Make sure that all the member variables are private to avoid accidental modification.
        It may be wise to clean up after setting the variables using the cleanup method (which you also have to implement below)
        :param sign: The sign of the number (1 for positive and 0, -1 for negative)
        :param int_part: The integer part of the number, excluding the sign (nonnegative integer)
        :param non_repeat: The non-repeating digits after the decimal point as a list of digits (if there are no non-repeating digits after the decimal point, should be an empty array, [])
        :param repeat: The repeating digits after the decimal point as a list of digits (if there are no repeating digits after the decimal point, should be an empty array, [])
        """
        # doneTODO: IMPLEMENT THE BODY OF THE CONSTRUCTOR (Probably < 10 lines of code)
        self.__sign = sign
        self.__int_part = int_part
        self.__non_repeat = list(non_repeat)
        self.__repeat = list(repeat)
        self.cleanup()

    @classmethod
    def fromString(cls, s):
        """
        Creates a RepeatingDecimal object from a string representation. (of the format sign int_part.non_repeat[repeat part], no commas included)
        The string should be in the format: sign int_part.non_repeat[repeat part]
        This code should be helpful in debugging your code.
        :param s: The string representation of the RepeatingDecimal
        :return: A RepeatingDecimal object
        """
        pattern = r'^([+-]?)(\d+)(?:\.(\d*?))?(?:\[(\d+)\])?$'
        match = re.fullmatch(pattern, s.strip())

        sign_str, int_part, non_repeat, repeat = match.groups()

        sign = -1 if sign_str == '-' else 1
        int_part = int(int_part)
        non_repeat = [int(d) for d in (non_repeat or "")]
        repeat = [int(d) for d in (repeat or "")]

        return cls(sign, int_part, non_repeat, repeat)


    def cleanup(self):
        """
        Performs any carryover operations leading to >10 or <0 numbers in the digits in non_repeat and repeat needed to ensure the RepeatingDecimal is in a valid state (e.g., [-1] is converted to [8], [10] is converted to [1]).
        Also, ensures that the repeat is minimal (i.e., repeat is not [3,3], but just [3]) and absorbs any repeating digits from non_repeat.
        Ensure that the repeat [0], [9] are handled as well. (e.g., (0).[9] should be converted to just (1)), and remove any trailing zeros from non_repeat if there is no repeat.
        Be especially aware of the case when the integer part becomes negative, since it can lead to a second round update of non_repeat and repeat.
        """

        # TODO: IMPLEMENT THE BODY OF THE CLEANUP METHOD (The solution is about 70-80 lines of code with comments and spacing)
        """
        An overview:
        while True: (in a nutshell, run things that might change the integer part until the integer part is stable)
        - Perform carryover operations on the repeat part
        - Minimize the repeat part and handle special cases [0] and [9]
        - Perform carryover operations on the non-repeat part
        - If the integer part becomes negative, change the sign and negate all parts, then repeat the process
        end while
        - Remove any repeating digits from the end of the non-repeat part that match the last digit of the repeat part
        - If there is no repeat part, remove any trailing zeros from the non-repeat part
        """
        while True:
            # check for carryovers in repeat
            rpart=0
            nrup=0
            if len(self.__repeat)==0:
                rpart=0
            else:
                for i in range(len(self.__repeat)): # Automatic Carryovers!!!
                    rpart=rpart*10+self.__repeat[i]
                if rpart >= pow(10,len(self.__repeat))-1:
                    x=rpart//(pow(10,len(self.__repeat))-1)
                    rpart%=pow(10,len(self.__repeat))-1
                    nrup+=x
                elif rpart<0:
                    x=(-rpart-1)//(pow(10,len(self.__repeat))-1)+1
                    rpart+=x*(pow(10,len(self.__repeat))-1)
                    nrup-=x
                new_repeat=[]
                for i in range(len(self.__repeat)-1,-1,-1):
                    new_repeat.append(rpart%10)
                    rpart//=10
                new_repeat.reverse()
                self.__repeat=new_repeat

            # minimalize repeat and check for [0] and [9]
            if len(self.__repeat)>1:
                for l in range(1,len(self.__repeat)//2+1):
                    if len(self.__repeat)%l==0:
                        flag=True
                        for i in range(len(self.__repeat)-l):
                            if self.__repeat[i]!=self.__repeat[i+l]:
                                flag=False
                                break
                        if flag:
                            self.__repeat=self.__repeat[:l]
                            break
            if len(self.__repeat)==1:
                if self.__repeat[0]==0:
                    self.__repeat=[]
                elif self.__repeat[0]==9:
                    self.__repeat=[]
                    nrup+=1

            # update carryover and check for carryovers in non_repeat
            nrpart=0
            carry=0
            for i in range(len(self.__non_repeat)):
                nrpart=nrpart*10+self.__non_repeat[i]
            nrpart+=nrup
            if nrpart >= pow(10,len(self.__non_repeat)):
                x=nrpart//(pow(10,len(self.__non_repeat)))
                nrpart%=pow(10,len(self.__non_repeat))
                carry+=x
            elif nrpart<0:
                x=(-nrpart-1)//(pow(10,len(self.__non_repeat)))+1
                nrpart+=x*(pow(10,len(self.__non_repeat)))
                carry-=x
            new_non_repeat=[]
            for i in range(len(self.__non_repeat)-1,-1,-1):
                new_non_repeat.append(nrpart%10)
                nrpart//=10
            new_non_repeat.reverse()
            self.__non_repeat=new_non_repeat
            self.__int_part+=carry

            # if int_part<0, change signs and repeat
            if self.__int_part<0:
                self.__sign*=-1
                self.__int_part=-self.__int_part
                for i in range(len(self.__non_repeat)):
                    self.__non_repeat[i]=-self.__non_repeat[i]
                for i in range(len(self.__repeat)):
                    self.__repeat[i]=-self.__repeat[i]
                continue
            break

        # remove repeating digits from non_repeat
        if len(self.__repeat)>0:
            while len(self.__non_repeat)>0 and self.__non_repeat[-1]==self.__repeat[-1]:
                self.__non_repeat.pop()
                self.__repeat=self.__repeat[-1:]+self.__repeat[:-1]
        else:
            while len(self.__non_repeat)>0 and self.__non_repeat[-1]==0:
                self.__non_repeat.pop()

    # TODO: IMPLEMENT THE FOLLOWING OPERATION OVERLOADING METHODS

    # TODO: SIGN NEGATION HEADER (i.e., -x unary operator)
    def __neg__(self):
        """
        Returns a new RepeatingDecimal object with the sign negated.
        """
        # TODO: IMPLEMENT THE BODY OF THE SIGN NEGATION METHOD (The solution is about 1 line of code)
        return RepeatingDecimal(-self.__sign, self.__int_part, self.__non_repeat, self.__repeat)

    # TODO: ADDITION HEADER (i.e., x + y binary operator)
    def __add__(self, other):
        """
        Adds two RepeatingDecimal objects and returns a new RepeatingDecimal object.
        """
        # TODO: IMPLEMENT THE BODY OF THE ADDITION METHOD (The solution is about 20-25 lines of code with comments and spacing)
        int_part = self.__int_part * self.__sign + other.__int_part * other.__sign
        an=list(self.__non_repeat)
        bn=list(other.__non_repeat)
        ar=list(self.__repeat)
        br=list(other.__repeat)
        if self.__sign == -1:
            for i in range(len(an)):
                an[i]=-an[i]
            for i in range(len(ar)):
                ar[i]=-ar[i]
        if other.__sign == -1:
            for i in range(len(bn)):
                bn[i]=-bn[i]
            for i in range(len(br)):
                br[i]=-br[i]
        while len(an)>len(bn):
            if len(br)==0:
                bn.append(0)
            else:
                bn.append(br[0])
                br=br[1:]+br[:1]
        while len(an)<len(bn):
            if len(ar)==0:
                an.append(0)
            else:
                an.append(ar[0])
                ar=ar[1:]+ar[:1]

        for i in range(len(bn)):
            an[i]+=bn[i]

        if len(ar)==0:
            ar=[0]
        if len(br)==0:
            br=[0]
        l=math.lcm(len(ar),len(br))
        ar=ar*(l//len(ar))
        br=br*(l//len(br))
        out=[]
        for i in range(l):
            out.append(ar[i]+br[i])
        return RepeatingDecimal(1, int_part, an, out)


    # TODO: SUBTRACTION HEADER (i.e., x - y binary operator)
    def __sub__(self, other):
        """
        Subtracts another RepeatingDecimal object from this one and returns a new RepeatingDecimal object.
        """
        # TODO: IMPLEMENT THE BODY OF THE SUBTRACTION METHOD (The solution is about 1 line of code, but can also take it in another direction with more lines of code)
        return self + (-other)

    # TODO: STRING REPRESENTATION HEADER -- THIS ONE IS OPTIONAL, BUT CAN BE HELPFUL FOR DEBUGGING
    def __str__(self):
        """
        Returns a string representation of the RepeatingDecimal.
        The format is: sign int_part.non_repeat[repeat part]
        If the non_repeat or repeat parts are empty, they are omitted (along with the decimal point if both are empty).
        """
        # TODO: IMPLEMENT THE BODY OF THE STRING REPRESENTATION METHOD (The solution is about 5-10 lines of code)
        x=""
        if self.__sign==-1:
            x+="-"
        x+=str(self.__int_part)
        if len(self.__non_repeat)>0 or len(self.__repeat)>0:
            x+="."
        for i in self.__non_repeat:
            x+=str(i)
        if len(self.__repeat)>0:
            x+="["+"".join(map(str,self.__repeat))+"]"
        return x

    # def __mul__(self, other):



if __name__ == "__main__":
    a = RepeatingDecimal.fromString("0.[3]")
    b = RepeatingDecimal.fromString("0.[6]")
    print(f"{a} + {b} = {a + b}")

    c = RepeatingDecimal.fromString("0.123[4567]")
    d = RepeatingDecimal.fromString("0.[01234]")
    print(f"{c} - {d} = {c - d}")

    e = RepeatingDecimal.fromString("3.14")
    f = RepeatingDecimal.fromString("-1.2[3]")
    print(f"{e} + {f} = {e + f}")

    h = RepeatingDecimal.fromString("0.[8]")
    i = RepeatingDecimal.fromString("0.[7]")
    print(f"{h} + {i} = {h + i}")

