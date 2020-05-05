public class step {
    public static int leapYearCount(int year) {
        int diff = ((year % 4) & (year % 100)) | year % 400;
        return (year - diff) / 4;
    }
}