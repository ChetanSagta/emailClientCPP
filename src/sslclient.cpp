#include "sslclient.h"
#include "openssl/err.h"

SSLClient::SSLClient(const SSL_METHOD* ssl_method, const std::string hostname, const std::string port) : m_method(ssl_method), m_hostname(hostname), m_port(port){
  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();

  m_context = SSL_CTX_new(ssl_method);
  m_ssl = SSL_new(m_context);
  SSL_set_connect_state(m_ssl);
  m_bio = BIO_new_ssl_connect(m_context);
  if (m_bio == NULL) {
    ERR_print_errors_fp(stderr);
    SSL_CTX_free(m_context);
    return;
  }

  BIO_set_conn_hostname(m_bio, (m_hostname + ":" + m_port).c_str());
  // Establish the connection
  if (BIO_do_connect(m_bio) <= 0) {
    ERR_print_errors_fp(stderr);
    BIO_free_all(m_bio);
    SSL_CTX_free(m_context);
    return;
  }
  // Get the SSL object
  if (BIO_get_ssl(m_bio, &m_ssl) <= 0) {
    ERR_print_errors_fp(stderr);
    BIO_free_all(m_bio);
    SSL_CTX_free(m_context);
    return;
  }

}

SSLClient::~SSLClient(){
  BIO_free_all(m_bio);
  SSL_CTX_free(m_context);
}


void SSLClient::read_ssl() {
	char buffer[1024];
	while ((m_ret = BIO_read(m_bio, buffer, sizeof(buffer) - 1)) > 0) {
	  buffer[m_ret] = '\0';
	  std::cout<<buffer<<std::endl;
	}
  }

int SSLClient::write_ssl(std::string request) {
  m_ret = BIO_write(m_bio, request.c_str(), request.length());
  if (m_ret <= 0) {
	ERR_print_errors_fp(stderr);
	BIO_free_all(m_bio);
	SSL_CTX_free(m_context);
	return 1;
  }
  return 0;
}
