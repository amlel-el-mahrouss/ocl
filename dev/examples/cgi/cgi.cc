/*
  cgi example
  written by Amlal El Mahrouss.
  licensed under the MIT license
 */

#include <lib/utility/cgi.hpp>
#include <fstream>
#include <sstream>
#include <string>

const std::string error_html = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Error | SOCL</title>
  <style>
    body {
      font-family: monospace;
      background: white;
      color: black;
      margin: 2em;
    }
    h1 {
      font-size: 1.5em;
    }
    hr {
      border: none;
      border-top: 1px solid #ccc;
    }
    table {
      width: 100%;
      border-collapse: collapse;
    }
    td {
      padding: 0.2em 0.5em;
    }
    td:first-child {
      white-space: nowrap;
    }
    a {
      color: blue;
      text-decoration: none;
    }
    a:hover {
      text-decoration: underline;
    }
  </style>
</head>
<body>
  <h1>Uh Oh!</h1>
  <address>No index file was found in this directory.</address>
  <hr>
  <table>
    <tr><th>Name</th></tr>
    <tr><td colspan="3"><hr></td></tr>

    <tr>
      <td><a href="javascript:window.location.reload();">Refresh</a></td>
    </tr>

    <tr><td colspan="3"><hr></td></tr>
  </table>
  <address>SOCL's Common Gateway Server.</address>
</body>
</html>
)";

/* finally test it */
/* @brief this stub loads a 'index.html' or returns an error message if not found. */
int main(int argc, char** argv)
{
	snu::cgi::basic_writer<> writer;

	std::stringstream		 ss_file;
	ss_file << error_html;

	writer.html(ss_file);

	return 0;
}
