<?hh // strict
namespace Decouple\Console;
class Command {
  /**
   * We're going to reflect on the execute method to determine the type of parameters
   * So we must make sure this method exists in our constructor
   */
  public function __construct() {
    if(!method_exists($this, 'execute')) {
      throw new \Exception("Error: Command must provide an execute function");
    }
  }
}
