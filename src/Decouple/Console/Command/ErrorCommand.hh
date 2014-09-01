<?hh // strict
namespace Decouple\Console\Command;
class ErrorCommand extends \Decouple\Console\Command
{
  public function __construct(public string $message="") 
  {
    parent::__construct();
  }
  public function execute() : void
  {
    echo "An unexpected error has occurred.\n";
    echo $this->message . "\n";
  }
}
