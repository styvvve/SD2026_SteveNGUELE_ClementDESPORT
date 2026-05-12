package domain.cli;

/**
 * This class (record) is used to answer the user in the CLI. The idea and the code is essentially a paste from the "reservation-engine"
 * practical classes in CSI
 * @param success
 * @param data
 * @param <T>
 */
public record Response<T>(boolean success, T data) {

    public static <T> Response<T> ok(T v) {
        return new Response<>(true, v);
    }

    public static <T> Response<T> fail(String message) {
        return new Response<>(false, null);
    }

    public boolean isOk() {
        return this.success;
    }
}
