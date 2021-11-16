#include <iostream>
#include <string>
#include <stdlib.h>

void set_content_type(std::string content_type)
{
  std::cout << "Content-type: " << content_type << "\r\n\r\n";
}

void set_page_title(std::string title)
{
  std::cout << "<title>" << title << "</title>\n";
}

void h1_text(std::string text)
{
  std::cout << text << "\n";
}

int main() {
  set_content_type("text/html");  // Output HTML boilerplate
  std::cout << "<!doctype html>\n";
  std::cout << "<html lang=\"en\">\n";
  std::cout << "<head>\n";
  set_page_title("Hello, World!");
  std::cout << "</head>\n";
  std::cout << "<body>\n";
  h1_text("Hello, World!");
  std::cout << "</body>\n";
  std::cout << "</html>"; 
  return 0;
}