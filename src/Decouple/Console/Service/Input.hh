<?hh // strict
namespace Decouple\Console\Service;
class Input extends \Decouple\Decoupler\Service {
  public function __construct(
    public Vector<string> $arguments, public string $command, public string $filename
  ) {}
}
