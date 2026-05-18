package domain.cli;

/**
 * This class (record) is used to answer the user in the CLI. The idea and the code is essentially a paste from the "reservation-engine"
 * practical classes in CSI
 * @param success 1 if the command was successful, 0 otherwise
 * @param data the data to return, Game in general or null if an error occurred
 * @param <T> the type of the data
 * @param errorMessage the error message if something went wrong
 */
public record Response<T>(boolean success, T data, String errorMessage) {

    public static <T> Response<T> ok(T v) {
        return new Response<>(true, v, null);
    }

    public static <T> Response<T> fail(String message) {
        return new Response<>(false, null, message);
    }

    public boolean isOk() { return this.success; }
}
