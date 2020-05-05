import java.math.BigInteger;
import java.util.Arrays;
import java.lang.StringBuilder;


public class Quiz {
    /**
     * Just testing something.
     * @return something, u know, bleen.
     */
    public static String test() {
        int [] arrayTest = new int[0];
        return Arrays.toString(arrayTest);
    }
    /**
     * Checks if given <code>text</code> is a palindrome.
     *
     * @param text any string
     * @return <code>true</code> when <code>text</code> is a palindrome, <code>false</code> otherwise
     */
    public static boolean isPalindrome(String text) {
        String clearText = text.replaceAll("[^a-zA-Z0-9]", "");
        StringBuilder reversedClearText = new StringBuilder(clearText).reverse();
        boolean result = clearText.equalsIgnoreCase(reversedClearText.toString());
        return result;
    }

    /**
     * Calculates factorial of given <code>value</code>.
     *
     * @param value positive number
     * @return factorial of <code>value</code>
     */
    public static BigInteger factorial(int value) {
        if (value == 1) {
            //BigInteger factorialResult = new BigInteger("1");
            return BigInteger.ONE;
        }
        return new BigInteger(String.valueOf(value)).multiply(factorial(value - 1)); // your implementation here
    }

    /**
     * Merges two given sorted arrays into one
     *
     * @param a1 first sorted array
     * @param a2 second sorted array
     * @return new array containing all elements from a1 and a2, sorted
     */
    public static int[] mergeArrays(int[] a1, int[] a2) {
        int [] resultArray = new int[a1.length + a2.length];
        int index1 = 0, index2 = 0;
        while (index1 + index2 < resultArray.length) {
            if (index1 >= a1.length) {
                resultArray[index1 + index2] = a2[index2++];
            } else if (index2 >= a2.length) {
                resultArray[index1 + index2] = a1[index1++];
            } else if (a1[index1] < a2[index2]) {
                resultArray[index1 + index2] = a1[index1++];
            } else {
                resultArray[index1 + index2] = a2[index2++];
            }
        }
        return resultArray;
    }

    public static void main(String[] args) throws Exception {
        //String input = "Madam, I'm Adam!";
        int [] a1 = {0, 2, 2, 5};
        int [] a2 = {1, 3, 4};
        System.out.println(Arrays.toString(mergeArrays(a1, a2)));
    }
}