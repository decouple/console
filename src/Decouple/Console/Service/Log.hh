<?hh // strict
namespace Decouple\Console\Service;
class Log extends \Decouple\Decoupler\Service {
  /**
   * TODO: Add params for log file and echo
   */
  public function log(string $message) : void
  {
    echo "[" . (string)microtime(true) . "]\t" . $message . "\n";
  }
}
