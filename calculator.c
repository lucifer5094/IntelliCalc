#include <microhttpd.h>

static int answer_handler(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls)
{
    const char *page = "<html><body><h1>Calculator App</h1>"
                       "<form action=\"/calculate\" method=\"post\">"
                       "Expression: <input type=\"text\" name=\"expression\">"
                       "<input type=\"submit\" value=\"Calculate\"></form></body></html>";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(page),
                                               (void *)page,
                                               MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main()
{
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD,
                              8080, NULL, NULL,
                              &answer_handler, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    (void)getchar();

    MHD_stop_daemon(daemon);
    return 0;
}
