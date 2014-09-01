<?hh // strict
namespace Decouple\Console\Service;
class Env extends \Decouple\Decoupler\Service {
  public function __construct(public Map<string,string> $variables) {}
}
